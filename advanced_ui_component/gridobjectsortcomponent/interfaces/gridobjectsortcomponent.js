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
const ACCESSIBILITY_DOUBLE_CLICK = 'gridobjectsortcomponent_accessibility_single_finger_double_click';
const ACCESSIBILITY_COMPLETE_BUTTON = 'gridobjectsortcomponent_accessibility_complete_button';
const ACCESSIBILITY_RESIDENT_AREA = 'gridobjectsortcomponent_accessibility_resident_area_edit_state';
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
(function (f103) {
    f103['IMAGE_TEXT'] = 'image_text';
    f103['TEXT'] = 'text';
})(GridObjectSortComponentType || (GridObjectSortComponentType = {}));
class MenuItem {
    constructor(z102, a103, b103, c103, d103, e103) {
        this.value = z102;
        this.symbolStyle = a103;
        this.isEnabled = b103;
        this.action = d103;
        this.accessibilityText = c103;
        this.label = e103;
    }
}
export class GridObjectSortComponent extends ViewPU {
    constructor(q102, r102, s102, t102 = -1, u102 = undefined, v102) {
        super(q102, s102, t102, v102);
        if (typeof u102 === 'function') {
            this.paramsGenerator_ = u102;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(r102.options, this, 'options');
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
        this.__isOpenAccessibility = new ObservedPropertySimplePU(accessibility.isScreenReaderOpenSync(), this, 'isOpenAccessibility');
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
            }, this.getStringByResource(ACCESSIBILITY_COMPLETE_BUTTON))
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
            onConfigurationUpdated: (x102) => {
                let y102 = this.getUIContext();
                this.fontSizeScale = this.decideFontScale(y102);
                this.fontWeightScale = x102.fontWeightScale;
            },
            onMemoryLevel: (w102) => { }
        };
        this.setInitiallyProvidedValue(r102);
        this.declareWatch('gridComState', this.onGridComStateChange);
        this.declareWatch('fontSizeScale', this.calcAreaInfo);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(p102) {
        if (p102.options === undefined) {
            this.__options.set({});
        }
        if (p102.dataList !== undefined) {
            this.dataList = p102.dataList;
        }
        if (p102.selected !== undefined) {
            this.selected = p102.selected;
        }
        if (p102.unSelected !== undefined) {
            this.unSelected = p102.unSelected;
        }
        if (p102.copySelected !== undefined) {
            this.copySelected = p102.copySelected;
        }
        if (p102.copyUnSelected !== undefined) {
            this.copyUnSelected = p102.copyUnSelected;
        }
        if (p102.content !== undefined) {
            this.content = p102.content;
        }
        if (p102.dragContent !== undefined) {
            this.dragContent = p102.dragContent;
        }
        if (p102.dragContentIndex !== undefined) {
            this.dragContentIndex = p102.dragContentIndex;
        }
        if (p102.hoverId !== undefined) {
            this.hoverId = p102.hoverId;
        }
        if (p102.gridComState !== undefined) {
            this.gridComState = p102.gridComState;
        }
        if (p102.menuSwitch !== undefined) {
            this.menuSwitch = p102.menuSwitch;
        }
        if (p102.areaWidth !== undefined) {
            this.areaWidth = p102.areaWidth;
        }
        if (p102.blockWidth !== undefined) {
            this.blockWidth = p102.blockWidth;
        }
        if (p102.blockHeight !== undefined) {
            this.blockHeight = p102.blockHeight;
        }
        if (p102.longScaleOnePointTwo !== undefined) {
            this.longScaleOnePointTwo = p102.longScaleOnePointTwo;
        }
        if (p102.scaleGridItemNinetyPercent !== undefined) {
            this.scaleGridItemNinetyPercent = p102.scaleGridItemNinetyPercent;
        }
        if (p102.reboundSize !== undefined) {
            this.reboundSize = p102.reboundSize;
        }
        if (p102.scaleIcon !== undefined) {
            this.scaleIcon = p102.scaleIcon;
        }
        if (p102.addIconShow !== undefined) {
            this.addIconShow = p102.addIconShow;
        }
        if (p102.scaleAddIcon !== undefined) {
            this.scaleAddIcon = p102.scaleAddIcon;
        }
        if (p102.isStartDrag !== undefined) {
            this.isStartDrag = p102.isStartDrag;
        }
        if (p102.insertIndex !== undefined) {
            this.insertIndex = p102.insertIndex;
        }
        if (p102.itemIndex !== undefined) {
            this.itemIndex = p102.itemIndex;
        }
        if (p102.editGridDataLength !== undefined) {
            this.editGridDataLength = p102.editGridDataLength;
        }
        if (p102.isTouchDown !== undefined) {
            this.isTouchDown = p102.isTouchDown;
        }
        if (p102.addItemMoveX !== undefined) {
            this.addItemMoveX = p102.addItemMoveX;
        }
        if (p102.addItemMoveY !== undefined) {
            this.addItemMoveY = p102.addItemMoveY;
        }
        if (p102.editItemMoveX !== undefined) {
            this.editItemMoveX = p102.editItemMoveX;
        }
        if (p102.editItemMoveY !== undefined) {
            this.editItemMoveY = p102.editItemMoveY;
        }
        if (p102.unSelectedIndex !== undefined) {
            this.unSelectedIndex = p102.unSelectedIndex;
        }
        if (p102.clickAddBtn !== undefined) {
            this.clickAddBtn = p102.clickAddBtn;
        }
        if (p102.selectedIndex !== undefined) {
            this.selectedIndex = p102.selectedIndex;
        }
        if (p102.clickRemoveBtn !== undefined) {
            this.clickRemoveBtn = p102.clickRemoveBtn;
        }
        if (p102.addAreaLongPressGesture !== undefined) {
            this.addAreaLongPressGesture = p102.addAreaLongPressGesture;
        }
        if (p102.arraySelectIsChange !== undefined) {
            this.arraySelectIsChange = p102.arraySelectIsChange;
        }
        if (p102.arrayUnSelectIsChange !== undefined) {
            this.arrayUnSelectIsChange = p102.arrayUnSelectIsChange;
        }
        if (p102.textItemEditWidth !== undefined) {
            this.textItemEditWidth = p102.textItemEditWidth;
        }
        if (p102.textItemEditHeight !== undefined) {
            this.textItemEditHeight = p102.textItemEditHeight;
        }
        if (p102.imageItemWidth !== undefined) {
            this.imageItemWidth = p102.imageItemWidth;
        }
        if (p102.saveClick !== undefined) {
            this.saveClick = p102.saveClick;
        }
        if (p102.imageTextAddIconShow !== undefined) {
            this.imageTextAddIconShow = p102.imageTextAddIconShow;
        }
        if (p102.imageTextRemoveIconShow !== undefined) {
            this.imageTextRemoveIconShow = p102.imageTextRemoveIconShow;
        }
        if (p102.firstIn !== undefined) {
            this.firstIn = p102.firstIn;
        }
        if (p102.fontSizeScale !== undefined) {
            this.fontSizeScale = p102.fontSizeScale;
        }
        if (p102.fontWeightScale !== undefined) {
            this.fontWeightScale = p102.fontWeightScale;
        }
        if (p102.customColumns !== undefined) {
            this.customColumns = p102.customColumns;
        }
        if (p102.editGridHeight !== undefined) {
            this.editGridHeight = p102.editGridHeight;
        }
        if (p102.addGridHeight !== undefined) {
            this.addGridHeight = p102.addGridHeight;
        }
        if (p102.subTitleHeight !== undefined) {
            this.subTitleHeight = p102.subTitleHeight;
        }
        if (p102.isOpenAccessibility !== undefined) {
            this.isOpenAccessibility = p102.isOpenAccessibility;
        }
        if (p102.callbackId !== undefined) {
            this.callbackId = p102.callbackId;
        }
        if (p102.colNum !== undefined) {
            this.colNum = p102.colNum;
        }
        if (p102.vibrationDone !== undefined) {
            this.vibrationDone = p102.vibrationDone;
        }
        if (p102.touchDown !== undefined) {
            this.touchDown = p102.touchDown;
        }
        if (p102.touchBorderRadius !== undefined) {
            this.touchBorderRadius = p102.touchBorderRadius;
        }
        if (p102.hoverBackgroundColor !== undefined) {
            this.hoverBackgroundColor = p102.hoverBackgroundColor;
        }
        if (p102.focusBorder !== undefined) {
            this.focusBorder = p102.focusBorder;
        }
        if (p102.imageText !== undefined) {
            this.imageText = p102.imageText;
        }
        if (p102.menuItems !== undefined) {
            this.menuItems = p102.menuItems;
        }
        if (p102.onSave !== undefined) {
            this.onSave = p102.onSave;
        }
        if (p102.onCancel !== undefined) {
            this.onCancel = p102.onCancel;
        }
        if (p102.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = p102.isFollowingSystemFontScale;
        }
        if (p102.maxAppFontScale !== undefined) {
            this.maxAppFontScale = p102.maxAppFontScale;
        }
        if (p102.bundleName !== undefined) {
            this.bundleName = p102.bundleName;
        }
        if (p102.readFlag !== undefined) {
            this.readFlag = p102.readFlag;
        }
        if (p102.readIndex4AddArea !== undefined) {
            this.readIndex4AddArea = p102.readIndex4AddArea;
        }
        if (p102.readIndex4EditArea !== undefined) {
            this.readIndex4EditArea = p102.readIndex4EditArea;
        }
        if (p102.isPointToAddTitleBarEditButton !== undefined) {
            this.isPointToAddTitleBarEditButton = p102.isPointToAddTitleBarEditButton;
        }
        if (p102.isPointToEditTitleBarSaveButton !== undefined) {
            this.isPointToEditTitleBarSaveButton = p102.isPointToEditTitleBarSaveButton;
        }
        if (p102.preTextAnnouncedForAccessibility !== undefined) {
            this.preTextAnnouncedForAccessibility = p102.preTextAnnouncedForAccessibility;
        }
        if (p102.textAnnouncedForAccessibility !== undefined) {
            this.textAnnouncedForAccessibility = p102.textAnnouncedForAccessibility;
        }
        if (p102.envCallback !== undefined) {
            this.envCallback = p102.envCallback;
        }
    }
    updateStateVars(o102) {
        this.__options.reset(o102.options);
    }
    purgeVariableDependenciesOnElmtId(n102) {
        this.__options.purgeDependencyOnElmtId(n102);
        this.__selected.purgeDependencyOnElmtId(n102);
        this.__unSelected.purgeDependencyOnElmtId(n102);
        this.__copySelected.purgeDependencyOnElmtId(n102);
        this.__copyUnSelected.purgeDependencyOnElmtId(n102);
        this.__content.purgeDependencyOnElmtId(n102);
        this.__dragContent.purgeDependencyOnElmtId(n102);
        this.__dragContentIndex.purgeDependencyOnElmtId(n102);
        this.__hoverId.purgeDependencyOnElmtId(n102);
        this.__gridComState.purgeDependencyOnElmtId(n102);
        this.__menuSwitch.purgeDependencyOnElmtId(n102);
        this.__areaWidth.purgeDependencyOnElmtId(n102);
        this.__blockWidth.purgeDependencyOnElmtId(n102);
        this.__blockHeight.purgeDependencyOnElmtId(n102);
        this.__longScaleOnePointTwo.purgeDependencyOnElmtId(n102);
        this.__scaleGridItemNinetyPercent.purgeDependencyOnElmtId(n102);
        this.__reboundSize.purgeDependencyOnElmtId(n102);
        this.__scaleIcon.purgeDependencyOnElmtId(n102);
        this.__addIconShow.purgeDependencyOnElmtId(n102);
        this.__scaleAddIcon.purgeDependencyOnElmtId(n102);
        this.__isStartDrag.purgeDependencyOnElmtId(n102);
        this.__insertIndex.purgeDependencyOnElmtId(n102);
        this.__itemIndex.purgeDependencyOnElmtId(n102);
        this.__editGridDataLength.purgeDependencyOnElmtId(n102);
        this.__isTouchDown.purgeDependencyOnElmtId(n102);
        this.__addItemMoveX.purgeDependencyOnElmtId(n102);
        this.__addItemMoveY.purgeDependencyOnElmtId(n102);
        this.__editItemMoveX.purgeDependencyOnElmtId(n102);
        this.__editItemMoveY.purgeDependencyOnElmtId(n102);
        this.__unSelectedIndex.purgeDependencyOnElmtId(n102);
        this.__clickAddBtn.purgeDependencyOnElmtId(n102);
        this.__selectedIndex.purgeDependencyOnElmtId(n102);
        this.__clickRemoveBtn.purgeDependencyOnElmtId(n102);
        this.__addAreaLongPressGesture.purgeDependencyOnElmtId(n102);
        this.__arraySelectIsChange.purgeDependencyOnElmtId(n102);
        this.__arrayUnSelectIsChange.purgeDependencyOnElmtId(n102);
        this.__textItemEditWidth.purgeDependencyOnElmtId(n102);
        this.__textItemEditHeight.purgeDependencyOnElmtId(n102);
        this.__imageItemWidth.purgeDependencyOnElmtId(n102);
        this.__saveClick.purgeDependencyOnElmtId(n102);
        this.__imageTextAddIconShow.purgeDependencyOnElmtId(n102);
        this.__imageTextRemoveIconShow.purgeDependencyOnElmtId(n102);
        this.__firstIn.purgeDependencyOnElmtId(n102);
        this.__fontSizeScale.purgeDependencyOnElmtId(n102);
        this.__fontWeightScale.purgeDependencyOnElmtId(n102);
        this.__customColumns.purgeDependencyOnElmtId(n102);
        this.__editGridHeight.purgeDependencyOnElmtId(n102);
        this.__addGridHeight.purgeDependencyOnElmtId(n102);
        this.__subTitleHeight.purgeDependencyOnElmtId(n102);
        this.__isOpenAccessibility.purgeDependencyOnElmtId(n102);
        this.__readFlag.purgeDependencyOnElmtId(n102);
        this.__readIndex4AddArea.purgeDependencyOnElmtId(n102);
        this.__readIndex4EditArea.purgeDependencyOnElmtId(n102);
        this.__isPointToAddTitleBarEditButton.purgeDependencyOnElmtId(n102);
        this.__isPointToEditTitleBarSaveButton.purgeDependencyOnElmtId(n102);
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
        this.__isOpenAccessibility.aboutToBeDeleted();
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
    set options(m102) {
        this.__options.set(m102);
    }
    get selected() {
        return this.__selected.get();
    }
    set selected(l102) {
        this.__selected.set(l102);
    }
    get unSelected() {
        return this.__unSelected.get();
    }
    set unSelected(k102) {
        this.__unSelected.set(k102);
    }
    get copySelected() {
        return this.__copySelected.get();
    }
    set copySelected(j102) {
        this.__copySelected.set(j102);
    }
    get copyUnSelected() {
        return this.__copyUnSelected.get();
    }
    set copyUnSelected(i102) {
        this.__copyUnSelected.set(i102);
    }
    get content() {
        return this.__content.get();
    }
    set content(h102) {
        this.__content.set(h102);
    }
    get dragContent() {
        return this.__dragContent.get();
    }
    set dragContent(g102) {
        this.__dragContent.set(g102);
    }
    get dragContentIndex() {
        return this.__dragContentIndex.get();
    }
    set dragContentIndex(f102) {
        this.__dragContentIndex.set(f102);
    }
    get hoverId() {
        return this.__hoverId.get();
    }
    set hoverId(e102) {
        this.__hoverId.set(e102);
    }
    get gridComState() {
        return this.__gridComState.get();
    }
    set gridComState(d102) {
        this.__gridComState.set(d102);
    }
    get menuSwitch() {
        return this.__menuSwitch.get();
    }
    set menuSwitch(c102) {
        this.__menuSwitch.set(c102);
    }
    get areaWidth() {
        return this.__areaWidth.get();
    }
    set areaWidth(b102) {
        this.__areaWidth.set(b102);
    }
    get blockWidth() {
        return this.__blockWidth.get();
    }
    set blockWidth(a102) {
        this.__blockWidth.set(a102);
    }
    get blockHeight() {
        return this.__blockHeight.get();
    }
    set blockHeight(z101) {
        this.__blockHeight.set(z101);
    }
    get longScaleOnePointTwo() {
        return this.__longScaleOnePointTwo.get();
    }
    set longScaleOnePointTwo(y101) {
        this.__longScaleOnePointTwo.set(y101);
    }
    get scaleGridItemNinetyPercent() {
        return this.__scaleGridItemNinetyPercent.get();
    }
    set scaleGridItemNinetyPercent(x101) {
        this.__scaleGridItemNinetyPercent.set(x101);
    }
    get reboundSize() {
        return this.__reboundSize.get();
    }
    set reboundSize(w101) {
        this.__reboundSize.set(w101);
    }
    get scaleIcon() {
        return this.__scaleIcon.get();
    }
    set scaleIcon(v101) {
        this.__scaleIcon.set(v101);
    }
    get addIconShow() {
        return this.__addIconShow.get();
    }
    set addIconShow(u101) {
        this.__addIconShow.set(u101);
    }
    get scaleAddIcon() {
        return this.__scaleAddIcon.get();
    }
    set scaleAddIcon(t101) {
        this.__scaleAddIcon.set(t101);
    }
    get isStartDrag() {
        return this.__isStartDrag.get();
    }
    set isStartDrag(s101) {
        this.__isStartDrag.set(s101);
    }
    get insertIndex() {
        return this.__insertIndex.get();
    }
    set insertIndex(r101) {
        this.__insertIndex.set(r101);
    }
    get itemIndex() {
        return this.__itemIndex.get();
    }
    set itemIndex(q101) {
        this.__itemIndex.set(q101);
    }
    get editGridDataLength() {
        return this.__editGridDataLength.get();
    }
    set editGridDataLength(p101) {
        this.__editGridDataLength.set(p101);
    }
    get isTouchDown() {
        return this.__isTouchDown.get();
    }
    set isTouchDown(o101) {
        this.__isTouchDown.set(o101);
    }
    get addItemMoveX() {
        return this.__addItemMoveX.get();
    }
    set addItemMoveX(n101) {
        this.__addItemMoveX.set(n101);
    }
    get addItemMoveY() {
        return this.__addItemMoveY.get();
    }
    set addItemMoveY(m101) {
        this.__addItemMoveY.set(m101);
    }
    get editItemMoveX() {
        return this.__editItemMoveX.get();
    }
    set editItemMoveX(l101) {
        this.__editItemMoveX.set(l101);
    }
    get editItemMoveY() {
        return this.__editItemMoveY.get();
    }
    set editItemMoveY(k101) {
        this.__editItemMoveY.set(k101);
    }
    get unSelectedIndex() {
        return this.__unSelectedIndex.get();
    }
    set unSelectedIndex(j101) {
        this.__unSelectedIndex.set(j101);
    }
    get clickAddBtn() {
        return this.__clickAddBtn.get();
    }
    set clickAddBtn(i101) {
        this.__clickAddBtn.set(i101);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(h101) {
        this.__selectedIndex.set(h101);
    }
    get clickRemoveBtn() {
        return this.__clickRemoveBtn.get();
    }
    set clickRemoveBtn(g101) {
        this.__clickRemoveBtn.set(g101);
    }
    get addAreaLongPressGesture() {
        return this.__addAreaLongPressGesture.get();
    }
    set addAreaLongPressGesture(f101) {
        this.__addAreaLongPressGesture.set(f101);
    }
    get arraySelectIsChange() {
        return this.__arraySelectIsChange.get();
    }
    set arraySelectIsChange(e101) {
        this.__arraySelectIsChange.set(e101);
    }
    get arrayUnSelectIsChange() {
        return this.__arrayUnSelectIsChange.get();
    }
    set arrayUnSelectIsChange(d101) {
        this.__arrayUnSelectIsChange.set(d101);
    }
    get textItemEditWidth() {
        return this.__textItemEditWidth.get();
    }
    set textItemEditWidth(c101) {
        this.__textItemEditWidth.set(c101);
    }
    get textItemEditHeight() {
        return this.__textItemEditHeight.get();
    }
    set textItemEditHeight(b101) {
        this.__textItemEditHeight.set(b101);
    }
    get imageItemWidth() {
        return this.__imageItemWidth.get();
    }
    set imageItemWidth(a101) {
        this.__imageItemWidth.set(a101);
    }
    get saveClick() {
        return this.__saveClick.get();
    }
    set saveClick(z100) {
        this.__saveClick.set(z100);
    }
    get imageTextAddIconShow() {
        return this.__imageTextAddIconShow.get();
    }
    set imageTextAddIconShow(y100) {
        this.__imageTextAddIconShow.set(y100);
    }
    get imageTextRemoveIconShow() {
        return this.__imageTextRemoveIconShow.get();
    }
    set imageTextRemoveIconShow(x100) {
        this.__imageTextRemoveIconShow.set(x100);
    }
    get firstIn() {
        return this.__firstIn.get();
    }
    set firstIn(w100) {
        this.__firstIn.set(w100);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(v100) {
        this.__fontSizeScale.set(v100);
    }
    get fontWeightScale() {
        return this.__fontWeightScale.get();
    }
    set fontWeightScale(u100) {
        this.__fontWeightScale.set(u100);
    }
    get customColumns() {
        return this.__customColumns.get();
    }
    set customColumns(t100) {
        this.__customColumns.set(t100);
    }
    get editGridHeight() {
        return this.__editGridHeight.get();
    }
    set editGridHeight(s100) {
        this.__editGridHeight.set(s100);
    }
    get addGridHeight() {
        return this.__addGridHeight.get();
    }
    set addGridHeight(r100) {
        this.__addGridHeight.set(r100);
    }
    get subTitleHeight() {
        return this.__subTitleHeight.get();
    }
    set subTitleHeight(q100) {
        this.__subTitleHeight.set(q100);
    }
    get isOpenAccessibility() {
        return this.__isOpenAccessibility.get();
    }
    set isOpenAccessibility(p100) {
        this.__isOpenAccessibility.set(p100);
    }
    get readFlag() {
        return this.__readFlag.get();
    }
    set readFlag(o100) {
        this.__readFlag.set(o100);
    }
    get readIndex4AddArea() {
        return this.__readIndex4AddArea.get();
    }
    set readIndex4AddArea(n100) {
        this.__readIndex4AddArea.set(n100);
    }
    get readIndex4EditArea() {
        return this.__readIndex4EditArea.get();
    }
    set readIndex4EditArea(m100) {
        this.__readIndex4EditArea.set(m100);
    }
    get isPointToAddTitleBarEditButton() {
        return this.__isPointToAddTitleBarEditButton.get();
    }
    set isPointToAddTitleBarEditButton(l100) {
        this.__isPointToAddTitleBarEditButton.set(l100);
    }
    get isPointToEditTitleBarSaveButton() {
        return this.__isPointToEditTitleBarSaveButton.get();
    }
    set isPointToEditTitleBarSaveButton(k100) {
        this.__isPointToEditTitleBarSaveButton.set(k100);
    }
    aboutToAppear() {
        this.dataList.length = 50;
        this.selected = this.dataList && this.deduplicate(this.dataList).filter(j100 => j100.selected).sort(this.sortBy());
        this.unSelected = this.dataList && this.deduplicate(this.dataList).filter(i100 => !i100.selected).sort(this.sortBy());
        this.copySelected = this.selected.slice();
        this.copyUnSelected = this.unSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.imageText = this.options.type === GridObjectSortComponentType.IMAGE_TEXT;
        try {
            let h100 = this.getUIContext();
            this.isFollowingSystemFontScale = h100.isFollowingSystemFontScale();
            this.maxAppFontScale = h100.getMaxFontScale();
            this.fontSizeScale = this.decideFontScale(h100);
            this.fontWeightScale =
                h100.getHostContext()?.config.fontWeightScale ?? DEFAULT_FONT_WEIGHT_SCALE;
        }
        catch (e100) {
            let f100 = e100.code;
            let g100 = e100.message;
            hilog.error(0x3900, 'Ace', `GridObjectSortComponent Faild to init fontsizescale info, code:${f100}, message: ${g100}`);
        }
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        }
        catch (b100) {
            let c100 = b100.code;
            let d100 = b100.message;
            hilog.error(0x3900, 'Ace', `GridObjectSortComponent Faild to get environment param error: ${c100}, ${d100}`);
        }
        this.calcGridHeight();
        setTimeout(() => {
            this.firstIn = false;
        }, 500);
        this.bundleName = getContext(this)?.abilityInfo?.bundleName;
        accessibility.on('screenReaderStateChange', (a100) => {
            this.isOpenAccessibility = a100;
        });
    }
    getAdaptiveSymbolFontSize() {
        let z99 = this.fontSizeScale;
        if (!this.isFollowingSystemFontScale || z99 === undefined) {
            z99 = MIN_FONT_SCALE;
        }
        z99 = Math.min(MIN_SYMBOL_FONT_SCALE, z99);
        z99 = Math.max(z99, MIN_FONT_SCALE);
        return (z99 * SYMBOL_SIZE_12FP).toString() + 'vp';
    }
    getSymbolFontSizeFrom(y99) {
        if (y99 === undefined) {
            return SYMBOL_DEFAULT;
        }
        if (typeof y99 === 'number') {
            return y99.toString() + 'vp';
        }
        return y99;
    }
    calcTextItemEditHeight() {
        let x99 = MeasureText.measureTextSize({
            textContent: this.dataList[0]?.text ?? '',
            fontSize: `${(LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })?.value ??
                DEFAULT_TEXT_SIZE) * (this.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE)}vp`,
            overflow: TextOverflow.Ellipsis,
            maxLines: TEXT_MAX_LINES
        });
        this.textItemEditHeight = this.fontSizeScale === DEFAULT_FONT_SIZE_SCALE ?
            GRID_ITEM_HEIGHT_TEXT : px2vp(x99.height);
        this.textItemEditHeight = this.textItemEditHeight + PADDING_EIGHT * 2;
    }
    decideFontScale(v99) {
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        let w99 = v99.getHostContext()?.config.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE;
        return Math.min(w99, this.maxAppFontScale, MAX_FONT_SCALE);
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
    deduplicate(r99) {
        const s99 = [];
        r99.forEach(t99 => {
            if (!s99.some(u99 => u99.id === t99.id)) {
                s99.push(t99);
            }
        });
        return s99;
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
        return (p99, q99) => {
            return p99.order - q99.order;
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
            let n99 = this.getUIContext().getFrameNodeById(EDIT_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
            let o99 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `ImageMenuItem_${n99}_0`
            });
            accessibility.sendAccessibilityEvent(o99).then(() => {
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
            const l99 = this.getNewData(this.selected, true, 0);
            const m99 = this.getNewData(this.unSelected, false, this.selected.length);
            this.selected = l99;
            this.unSelected = m99;
            this.calcGridHeight();
            this.onSave && this.onSave(l99, m99);
        });
        setTimeout(() => {
            this.saveClick = false;
        }, ENTER_EXIT_ICON_DURATION);
        this.menuSwitch = false;
        this.isPointToAddTitleBarEditButton = true;
    }
    pointToAddTitleBarEditButton() {
        if (this.isPointToAddTitleBarEditButton) {
            let j99 = this.getUIContext()?.getFrameNodeById(ADD_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
            let k99 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `ComposeTitleBar_ImageMenuItem_${j99}_0`
            });
            accessibility.sendAccessibilityEvent(k99).then(() => {
                setTimeout(() => {
                    this.isPointToAddTitleBarEditButton = false;
                }, ENTER_EXIT_ICON_DURATION);
            });
        }
    }
    onDragMoveEvent(f99, g99, h99) {
        if (!this.gridComState || (f99.x < this.blockWidth / 3 && f99.y < this.blockHeight / 3)) {
            return;
        }
        let i99 = h99;
        if (i99 < 0) {
            i99 = this.selected.length - 1;
        }
        else {
            this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DRAG_MOVING, Math.floor(h99 / this.colNum) + 1, h99 % this.colNum + 1);
        }
        if (this.dragContent.visibility !== Visibility.Hidden) {
            this.dragContent.visibility = Visibility.Hidden;
        }
        if (this.insertIndex !== h99 || g99 !== h99) {
            this.sendAccessibility();
        }
        this.insertIndex = h99;
    }
    sendAccessibility() {
        if (this.preTextAnnouncedForAccessibility !== this.textAnnouncedForAccessibility) {
            let e99 = ({
                type: 'announceForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                textAnnouncedForAccessibility: this.textAnnouncedForAccessibility
            });
            accessibility.sendAccessibilityEvent(e99);
            this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
        }
    }
    handleDeleteClick(a99) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.clickRemoveBtn = true;
        this.scaleIcon = 0;
        this.arraySelectIsChange = 1;
        let b99 = this.selected.findIndex(d99 => d99.id === a99.id);
        this.content = a99;
        this.selectedIndex = b99;
        this.calcGridHeight();
        Context.animateTo({ curve: REMOVE_ADD_SPRING, onFinish: () => {
            this.scaleIcon = 1;
            this.selected.splice(b99, 1);
            this.unSelected.unshift(a99);
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
            let c99 = this.getAddItemGridPosition();
            this.editItemMoveX = c99.x;
            this.editItemMoveY = c99.y;
        });
    }
    pointToAddArea() {
        let z98 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: ADD_GRID_FIRST_ITEM_ID
        });
        accessibility.sendAccessibilityEvent(z98).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4AddArea = -1;
            }, ENTER_EXIT_ICON_DURATION);
        });
    }
    getNewData(u98, v98, w98) {
        return u98.map((x98, y98) => {
            x98.selected = v98;
            x98.order = w98 + y98;
            x98.visibility = Visibility.Visible;
            return x98;
        });
    }
    getBlockWidth() {
        const t98 = (this.areaWidth - 32) / this.colNum;
        return t98;
    }
    calcGridHeight() {
        this.editGridHeight = this.getGridHeight(this.selected, EDIT);
        this.addGridHeight = this.getGridHeight(this.unSelected);
    }
    getGridHeight(l98, m98) {
        let n98 = 0;
        let o98 = l98.length;
        l98.forEach(s98 => {
            if (s98.visibility === Visibility.Hidden) {
                o98 = o98 - 1;
            }
        });
        let p98 = 0;
        let q98 = o98 % this.colNum === 0;
        if (this.clickAddBtn && q98) {
            p98 = 1;
        }
        else if (this.isStartDrag && q98 && m98) {
            p98 = 1;
        }
        else if (this.clickRemoveBtn && q98 && !m98) {
            p98 = 1;
        }
        else {
            p98 = 0;
        }
        let r98 = Math.ceil(o98 / this.colNum) + p98;
        n98 = this.blockHeight * r98;
        if (o98 === 0) {
            n98 = 0;
        }
        return n98;
    }
    imageTextRemoveIcon(i98) {
        const j98 = this.clickRemoveBtn && this.content.id === i98.id;
        const k98 = j98 ? { 'id': -1, 'type': 40000, params: ['sys.symbol.plus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        return k98;
    }
    imageTextAddIcon(f98) {
        const g98 = this.clickAddBtn && this.content.id === f98.id && this.gridComState;
        const h98 = g98 ? { 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 40000, params: ['sys.symbol.plus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        return h98;
    }
    imageTextAddIconVisible(c98) {
        const d98 = this.clickAddBtn && this.content.id === c98.id && !this.gridComState;
        const e98 = d98 ? Visibility.Hidden : Visibility.Visible;
        return e98;
    }
    getCoodXY(x97) {
        let y97 = 0;
        let z97 = 0;
        const a98 = this.colNum;
        const b98 = Math.trunc(x97 % a98);
        if (x97 >= this.dragContentIndex) {
            if (x97 <= this.insertIndex && x97 !== this.dragContentIndex) {
                if (b98 === 0) {
                    y97 = y97 + this.blockWidth * (a98 - 1);
                    z97 = z97 - this.blockHeight;
                }
                else {
                    y97 = y97 - this.blockWidth;
                }
            }
        }
        else {
            if (x97 >= this.insertIndex) {
                if (b98 === a98 - 1) {
                    y97 = y97 - this.blockWidth * (a98 - 1);
                    z97 = z97 + this.blockHeight;
                }
                else {
                    y97 = y97 + this.blockWidth;
                }
            }
        }
        if (!this.isStartDrag) {
            y97 = 0;
            z97 = 0;
        }
        return { x: y97, y: z97 };
    }
    getAddItemGridPosition() {
        const l97 = this.selected.length;
        const m97 = this.colNum;
        const n97 = (this.selectedIndex + 1) % m97;
        const o97 = Math.ceil((this.selectedIndex + 1) / m97);
        const p97 = Math.ceil(l97 / m97);
        const q97 = this.imageText;
        let r97 = 0;
        if (n97 === 0) {
            r97 = q97 || (this.fontSizeScale && this.fontSizeScale > 1) ? -this.blockWidth * 2 : -this.blockWidth * 3;
        }
        else {
            r97 = -this.blockWidth * (n97 - 1);
        }
        let s97 = SUBTITLE_HEIGHT;
        let t97 = 0;
        const u97 = p97 - o97;
        const v97 = l97 % m97;
        const w97 = v97 === 1 ? u97 : u97 + 1;
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            s97 = this.subTitleHeight;
        }
        t97 = w97 * this.blockHeight + s97;
        return {
            x: r97,
            y: t97
        };
    }
    getCoveringGridPosition(i97) {
        let j97 = 0;
        let k97 = 0;
        if (i97 > this.selectedIndex && this.arraySelectIsChange !== 2) {
            j97 = i97 % this.colNum === 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            k97 = i97 % this.colNum === 0 ? -this.blockHeight : 0;
        }
        return {
            x: j97,
            y: k97
        };
    }
    getEditItemGridPosition(w96, x96) {
        const y96 = w96.length;
        const z96 = this.colNum;
        const a97 = Math.trunc(y96 % z96);
        const b97 = Math.trunc(x96 % z96);
        let c97 = Math.abs(a97 - b97) * this.blockWidth;
        if (a97 < b97) {
            c97 = -c97;
        }
        else if (a97 > b97) {
            c97 = c97;
        }
        else {
            c97 = 0;
        }
        let d97 = 0;
        let e97 = 0;
        let f97 = Math.trunc(x96 / this.colNum);
        let g97 = SUBTITLE_HEIGHT;
        const h97 = !this.imageText && this.gridComState && x96 > 3;
        if (h97) {
            e97 = (f97 + 1) * (this.blockHeight - 8) + 8;
        }
        else {
            e97 = (f97 + 1) * this.blockHeight;
        }
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            g97 = this.subTitleHeight;
        }
        d97 = e97 + g97;
        return {
            x: c97,
            y: d97
        };
    }
    getCoveringGridPositionBottom(r96) {
        let s96 = 0;
        let t96 = 0;
        const u96 = r96 % this.colNum === 0;
        const v96 = this.gridComState && !this.imageText ? -this.blockHeight + 8 : -this.blockHeight;
        if (r96 > this.unSelectedIndex && this.arrayUnSelectIsChange !== 2) {
            s96 = u96 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            t96 = u96 ? v96 : 0;
        }
        return {
            x: s96,
            y: t96
        };
    }
    getAddItemRightMove(n96) {
        let o96 = this.blockWidth;
        let p96 = 0;
        let q96 = (n96 + 1) % this.colNum === 0;
        if (q96) {
            o96 = -this.blockWidth * (this.colNum - 1);
            p96 = this.imageText ? this.blockHeight : this.blockHeight - 8;
        }
        return { x: o96, y: p96 };
    }
    getShowAreaItemTranslate(k96) {
        if (this.isStartDrag) {
            let m96 = this.getCoodXY(k96);
            return {
                x: m96.x,
                y: m96.y
            };
        }
        if (!this.isStartDrag && k96 === this.selectedIndex) {
            return {
                x: this.editItemMoveX,
                y: this.editItemMoveY
            };
        }
        if (!this.isStartDrag && k96 !== this.selectedIndex && this.clickRemoveBtn) {
            let l96 = this.getCoveringGridPosition(k96);
            return {
                x: l96.x,
                y: l96.y
            };
        }
        return { x: 0, y: 0 };
    }
    getAddAreaItemTranslate(h96) {
        if (this.clickRemoveBtn) {
            let j96 = this.getAddItemRightMove(h96);
            return {
                x: j96.x,
                y: j96.y
            };
        }
        if (!this.clickRemoveBtn && h96 === this.unSelectedIndex) {
            return {
                x: this.addItemMoveX,
                y: -this.addItemMoveY
            };
        }
        if (!this.clickRemoveBtn && h96 !== this.unSelectedIndex && this.clickAddBtn) {
            let i96 = this.getCoveringGridPositionBottom(h96);
            return {
                x: i96.x,
                y: i96.y
            };
        }
        return { x: 0, y: 0 };
    }
    PixelMapBuilder(g95, h95, i95 = null) {
        this.observeComponentCreation2((f96, g96) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.clip(false);
            Stack.height(this.blockHeight * 1.5);
            Stack.width(this.blockWidth * 1.2);
        }, Stack);
        this.observeComponentCreation2((j95, k95) => {
            If.create();
            if (this.imageText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d96, e96) => {
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
                    this.observeComponentCreation2((v95, w95) => {
                        If.create();
                        if (g95 === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((b96, c96) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.width(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.fontSize(this.options.imageSize || SYMBOL_DEFAULT);
                                }, SymbolGlyph);
                            });
                        }
                        else if (g95 instanceof SymbolGlyphModifier) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((z95, a96) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.width(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.attributeModifier.bind(this)(g95);
                                    SymbolGlyph.fontSize(this.options.imageSize || SYMBOL_DEFAULT);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                                this.observeComponentCreation2((x95, y95) => {
                                    Image.create(g95);
                                    Image.draggable(false);
                                    Image.height(this.options.imageSize || IMAGE_DEFAULT);
                                    Image.width(this.options.imageSize || IMAGE_DEFAULT);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((t95, u95) => {
                        Text.create(h95);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.margin({ top: 2 });
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((r95, s95) => {
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
                    this.observeComponentCreation2((p95, q95) => {
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
                    this.observeComponentCreation2((n95, o95) => {
                        Text.create(h95);
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.textAlign(TextAlign.Center);
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((l95, m95) => {
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
    HeaderTitleBuilder(o94 = null) {
        this.observeComponentCreation2((b95, c95) => {
            __Common__.create();
            __Common__.id(ADD_TITLE_BAR_ID);
            __Common__.visibility(!this.menuSwitch ? Visibility.Visible : Visibility.None);
            __Common__.onVisibleAreaChange([0.0, 1.0], (d95, e95) => {
                if (d95) {
                    this.pointToAddTitleBarEditButton();
                }
                else {
                    if (this.isPointToEditTitleBarSaveButton) {
                        let f95 = ({
                            type: 'announceForAccessibility',
                            bundleName: this.bundleName,
                            triggerAction: 'common',
                            textAnnouncedForAccessibility: getContext().resourceManager
                                .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE)
                        });
                        accessibility.sendAccessibilityEvent(f95);
                    }
                }
            });
        }, __Common__);
        {
            this.observeComponentCreation2((x94, y94) => {
                if (y94) {
                    let z94 = new ComposeTitleBar(this, {
                        title: this.options.normalTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        menuItems: this.menuItems,
                    }, undefined, x94, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 977, col: 5 });
                    ViewPU.create(z94);
                    let j = () => {
                        return {
                            title: this.options.normalTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            menuItems: this.menuItems
                        };
                    };
                    z94.paramsGenerator_ = j;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(x94, {});
                }
            }, { name: 'ComposeTitleBar' });
        }
        __Common__.pop();
        this.observeComponentCreation2((t94, u94) => {
            __Common__.create();
            __Common__.id(EDIT_TITLE_BAR_ID);
            __Common__.visibility(this.menuSwitch ? Visibility.Visible : Visibility.None);
            __Common__.onVisibleAreaChange([0.0, 1.0], (v94, w94) => {
                if (v94) {
                    this.pointToEditTitleBarSaveButton();
                }
            });
        }, __Common__);
        {
            this.observeComponentCreation2((p94, q94) => {
                if (q94) {
                    let r94 = new EditableTitleBar(this, {
                        leftIconStyle: EditableLeftIconType.Cancel,
                        isSaveIconRequired: false,
                        menuItems: [{
                            value: { 'id': -1, 'type': 40000, params: ['sys.symbol.checkmark'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            label: this.getStringByResource(ACCESSIBILITY_COMPLETE_BUTTON),
                            accessibilityText: this.getStringByResource(ACCESSIBILITY_COMPLETE_BUTTON),
                            action: () => {
                                this.saveClick = true;
                                this.onSaveEdit();
                            }
                        }],
                        title: this.options.editTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_edit'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        onCancel: () => {
                            this.cancelEdit();
                        },
                    }, undefined, p94, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 999, col: 5 });
                    ViewPU.create(r94);
                    let i = () => {
                        return {
                            leftIconStyle: EditableLeftIconType.Cancel,
                            isSaveIconRequired: false,
                            menuItems: [{
                                value: { 'id': -1, 'type': 40000, params: ['sys.symbol.checkmark'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                label: this.getStringByResource(ACCESSIBILITY_COMPLETE_BUTTON),
                                accessibilityText: this.getStringByResource(ACCESSIBILITY_COMPLETE_BUTTON),
                                action: () => {
                                    this.saveClick = true;
                                    this.onSaveEdit();
                                }
                            }],
                            title: this.options.editTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_edit'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            onCancel: () => {
                                this.cancelEdit();
                            }
                        };
                    };
                    r94.paramsGenerator_ = i;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(p94, {});
                }
            }, { name: 'EditableTitleBar' });
        }
        __Common__.pop();
    }
    ImageTextBuilder(r93, s93, t93 = null) {
        this.observeComponentCreation2((m94, n94) => {
            Column.create();
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((k94, l94) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Center);
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.height(this.imageItemWidth);
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.borderRadius((this.isTouchDown && r93.id === this.content.id) ||
                r93.id === this.hoverId ? this.touchBorderRadius : 0);
            Column.backgroundColor(this.isTouchDown && r93.id === this.content.id
                ? this.touchDown : r93.id === this.hoverId ? this.hoverBackgroundColor : '');
            Column.scale(r93.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
        }, Column);
        this.observeComponentCreation2((a94, b94) => {
            If.create();
            if (r93.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i94, j94) => {
                        SymbolGlyph.create();
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.attributeModifier.bind(this)(r93.symbolStyle);
                        SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((c94, d94) => {
                        If.create();
                        if (r93.url === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((g94, h94) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((e94, f94) => {
                                    Image.create(r93.url);
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
        this.observeComponentCreation2((y93, z93) => {
            Text.create(r93.text);
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
        this.observeComponentCreation2((w93, x93) => {
            SymbolGlyph.create(this.imageTextAddIcon(r93));
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.visibility(s93 === 'add' ? this.imageTextAddIconVisible(r93) : Visibility.Hidden);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.height(ICON_SIZE);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            SymbolGlyph.onClick(() => this.handleAddIconClick(r93));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResource(ACCESSIBILITY_UNSELECTED_BUTTON, `${r93.text ?? ''}`));
        }, SymbolGlyph);
        this.observeComponentCreation2((u93, v93) => {
            SymbolGlyph.create(this.imageTextRemoveIcon(r93));
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.visibility(s93 === 'delete' && this.gridComState ? Visibility.Visible :
            Visibility.Hidden);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.height(ICON_SIZE);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            SymbolGlyph.onClick(() => this.handleDeleteClick(r93));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DELETE, `${r93.text ?? ''}`));
        }, SymbolGlyph);
        Column.pop();
        Column.pop();
    }
    handleAddIconClick(m93) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.scaleIcon = 0;
        this.content = m93;
        const n93 = this.unSelected.findIndex(q93 => q93.id === m93.id);
        this.editGridDataLength = this.selected.length + 1;
        const o93 = this.getEditItemGridPosition(this.selected, n93);
        this.unSelectedIndex = n93;
        this.arrayUnSelectIsChange = 1;
        this.clickAddBtn = true;
        this.calcGridHeight();
        Context.animateTo({
            curve: REMOVE_ADD_SPRING,
            onFinish: () => {
                if (!this.selected.some(p93 => p93.id === m93.id)) {
                    this.arrayUnSelectIsChange = 2;
                    this.scaleIcon = 1;
                    this.selected.push(m93);
                    this.unSelected.splice(n93, 1);
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
            this.addItemMoveX = o93.x;
            this.addItemMoveY = o93.y;
        });
        this.readFlag = false;
        this.readIndex4EditArea = this.editGridDataLength - 1;
        this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_UNSELECTED_ITEM_ADD, `${this.content?.text ?? ''}`, Math.floor(this.readIndex4EditArea / this.colNum) + 1, this.readIndex4EditArea % this.colNum + 1);
    }
    TextBlockBuilder(y92, z92 = null) {
        this.observeComponentCreation2((k93, l93) => {
            Stack.create();
            Stack.scale(y92.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((i93, j93) => {
            Row.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
            } : { duration: 0 });
            Row.borderRadius(50);
            Row.width(this.clickRemoveBtn && y92.id === this.content.id ?
                this.textItemEditWidth + 8 : this.textItemEditWidth);
            Row.translate(this.gridComState ? this.clickRemoveBtn &&
                y92.id === this.content.id ? { x: 0 } : { x: -4 } : { x: 0 });
            Row.height('100%');
            Context.animation(null);
            Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((g93, h93) => {
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
            Flex.backgroundColor(this.isTouchDown && y92.id === this.content.id ? this.touchDown
                : y92.id === this.hoverId ? this.hoverBackgroundColor
                    : '');
            Flex.width(this.clickRemoveBtn && y92.id === this.content.id ?
                this.textItemEditWidth + 8 : this.textItemEditWidth);
            Flex.translate(this.gridComState ? this.clickRemoveBtn && y92.id === this.content.id ?
                { x: 0 } : { x: -4 } : { x: 0 });
            Flex.height('100%');
            Context.animation(null);
        }, Flex);
        this.observeComponentCreation2((e93, f93) => {
            SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.plus'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            SymbolGlyph.fontSize(this.getAdaptiveSymbolFontSize());
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.visibility(this.clickRemoveBtn && y92.id === this.content.id ? Visibility.Visible : Visibility.None);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0, } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((c93, d93) => {
            Text.create(y92.text);
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((a93, b93) => {
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
            SymbolGlyph.scale(y92.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon } : {});
            SymbolGlyph.visibility(this.gridComState ? 0 : 1);
            SymbolGlyph.position({
                x: this.blockWidth - 52,
                y: -MARGIN_EIGHT
            });
            Context.animation(null);
            SymbolGlyph.onClick(() => this.handleDeleteClick(y92));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DELETE, `${y92.text ?? ''}`));
        }, SymbolGlyph);
        Flex.pop();
        Stack.pop();
    }
    TextBlockAddItemBuilder(i92, j92 = null) {
        this.observeComponentCreation2((w92, x92) => {
            Stack.create();
            Stack.scale(i92.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((u92, v92) => {
            Row.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Row.borderRadius(50);
            Row.height('100%');
            Row.width(this.addIconShow && i92.id === this.content.id ? this.textItemEditWidth : '100%');
            Row.translate(this.addIconShow && i92.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((s92, t92) => {
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
            Flex.backgroundColor(this.isTouchDown && i92.id === this.content.id ? this.touchDown
                : i92.id === this.hoverId ? this.hoverBackgroundColor : '');
            Flex.width(this.addIconShow && i92.id === this.content.id ? this.textItemEditWidth : '100%');
            Flex.translate(this.addIconShow && i92.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Flex.height('100%');
        }, Flex);
        this.observeComponentCreation2((q92, r92) => {
            SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.plus'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            SymbolGlyph.fontSize(this.getAdaptiveSymbolFontSize());
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.visibility(this.addIconShow && i92.id === this.content.id ? Visibility.None : Visibility.Visible);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((o92, p92) => {
            Text.create(i92.text);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Start);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((k92, l92) => {
            If.create();
            if (this.gridComState && this.addIconShow && i92.id === this.content.id) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m92, n92) => {
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
    AddTagBuilder(n91 = null) {
        this.observeComponentCreation2((g92, h92) => {
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
        this.observeComponentCreation2((o91, p91) => {
            ForEach.create();
            const f = (s91, t91) => {
                const u91 = s91;
                {
                    const g = (e92, f92) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.clickRemoveBtn ? DRAG_SPRING : t91 === this.unSelectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getAddAreaItemTranslate(t91));
                        Context.animation(null);
                    };
                    const h = () => {
                        this.observeComponentCreation2(g, GridItem);
                        this.observeComponentCreation2((z91, a92) => {
                            Stack.create();
                            Stack.onHover((d92) => {
                                if (d92) {
                                    this.hoverId = u91.id;
                                }
                                else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.margin({
                                bottom: this.imageText ? ROW_GAP : MARGIN_EIGHT
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.onTouch(this.isOpenAccessibility ? undefined : (c92) => {
                                this.handleAddItemTouch(c92, u91);
                            });
                            Stack.onClick(this.isOpenAccessibility ? () => this.handleAddItemClick(u91) : undefined);
                            Gesture.create(GesturePriority.Low);
                            LongPressGesture.create({ repeat: true });
                            LongPressGesture.onAction((b92) => {
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
                            Stack.id(`add_grid_item_${t91}`);
                            Stack.onAppear(() => {
                                if (!this.readFlag && t91 === this.readIndex4AddArea) {
                                    this.pointToAddArea();
                                }
                            });
                            Stack.accessibilityGroup(true);
                            Stack.accessibilityLevel(YES);
                            Stack.accessibilityText(this.readFlag ?
                            this.getStringByResource(ACCESSIBILITY_UNSELECTED_ITEM, `${u91.text ?? ''}`) : this.textAnnouncedForAccessibility);
                            Stack.accessibilityDescription(this.readFlag ? this.getAddTagGridItemAccessibilityDesc() : ' ');
                        }, Stack);
                        this.observeComponentCreation2((x91, y91) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(u91, ADD);
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockAddItemBuilder.bind(this)(u91);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    h();
                }
            };
            this.forEachUpdateFunction(o91, this.unSelected, f, (r91) => r91.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
    }
    getAddTagGridItemAccessibilityDesc() {
        return this.options?.type === GridObjectSortComponentType.IMAGE_TEXT ?
            this.menuSwitch ? ' ' : this.getStringByResource(ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC) :
            this.menuSwitch ? this.getStringByResource(ACCESSIBILITY_DOUBLE_CLICK) :
            this.getStringByResource(ACCESSIBILITY_UNSELECTED_TEXT_ITEM_DESC);
    }
    handleAddItemTouch(h91, i91) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        if (h91.type === TouchType.Down) {
            this.content = i91;
            this.isTouchDown = true;
        }
        if (h91.type === TouchType.Cancel) {
            this.isTouchDown = false;
            return;
        }
        if (h91.type === TouchType.Up) {
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
            const j91 = this.unSelected.findIndex(m91 => m91.id === i91.id);
            this.editGridDataLength = this.selected.length + 1;
            const k91 = this.getEditItemGridPosition(this.selected, j91);
            this.content = i91;
            this.unSelectedIndex = j91;
            this.clickAddBtn = true;
            this.arrayUnSelectIsChange = 1;
            this.calcGridHeight();
            Context.animateTo({ curve: REMOVE_ADD_SPRING, onFinish: () => {
                if (!this.selected.some(l91 => l91.id === i91.id)) {
                    this.scaleIcon = 1;
                    this.scaleAddIcon = 0;
                    this.selected.push(i91);
                    this.unSelected.splice(j91, 1);
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
                this.addItemMoveX = k91.x;
                this.addItemMoveY = k91.y;
            });
            this.readFlag = false;
            this.readIndex4EditArea = this.editGridDataLength - 1;
            this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_UNSELECTED_ITEM_ADD, `${this.content?.text ?? ''}`, Math.floor(this.readIndex4EditArea / this.colNum) + 1, this.readIndex4EditArea % this.colNum + 1);
        }
    }
    handleAddItemClick(c91) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.content = c91;
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
        const d91 = this.unSelected.findIndex(g91 => g91.id === c91.id);
        this.editGridDataLength = this.selected.length + 1;
        const e91 = this.getEditItemGridPosition(this.selected, d91);
        this.content = c91;
        this.unSelectedIndex = d91;
        this.clickAddBtn = true;
        this.arrayUnSelectIsChange = 1;
        this.calcGridHeight();
        Context.animateTo({
            curve: REMOVE_ADD_SPRING,
            onFinish: () => {
                if (!this.selected.some(f91 => f91.id === c91.id)) {
                    this.scaleIcon = 1;
                    this.scaleAddIcon = 0;
                    this.selected.push(c91);
                    this.unSelected.splice(d91, 1);
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
            }
        }, () => {
            this.addItemMoveX = e91.x;
            this.addItemMoveY = e91.y;
        });
        this.readFlag = false;
        this.readIndex4EditArea = this.editGridDataLength - 1;
        this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_UNSELECTED_ITEM_ADD, `${this.content?.text ?? ''}`, Math.floor(this.readIndex4EditArea / this.colNum) + 1, this.readIndex4EditArea % this.colNum + 1);
    }
    EditTagBuilder(r89 = null) {
        this.observeComponentCreation2((z90, a91) => {
            Column.create();
            Column.accessibilityLevel((this.selected.length === 0) ? YES : NO);
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction(() => {
                this.menuSwitch = true;
            });
            LongPressGesture.onActionEnd(() => {
                let b91 = ({
                    type: 'announceForAccessibility',
                    bundleName: this.bundleName,
                    triggerAction: 'common',
                    textAnnouncedForAccessibility: getContext().resourceManager
                        .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE)
                });
                accessibility.sendAccessibilityEvent(b91);
            });
            LongPressGesture.pop();
            Gesture.pop();
            Column.accessibilityText(this.getStringByResource(ACCESSIBILITY_RESIDENT_AREA));
            Column.accessibilityDescription(this.menuSwitch ? ' ' :
            this.getStringByResource(ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC));
        }, Column);
        this.observeComponentCreation2((l90, m90) => {
            Grid.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            } : { duration: 0 });
            Grid.accessibilityLevel(NO);
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((y90) => {
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
                    if (y90.repeat && !this.vibrationDone) {
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
            Grid.onItemDragStart((w90, x90) => {
                this.itemIndex = x90;
                this.selectedIndex = -1;
                if (!this.gridComState) {
                    return;
                }
                this.isStartDrag = true;
                this.insertIndex = x90;
                this.dragContent = this.selected[x90];
                this.dragContentIndex = x90;
                this.textAnnouncedForAccessibility = getContext().resourceManager
                    .getStringByNameSync(ACCESSIBILITY_SELECTED_ITEM_DRAG_START, `${this.dragContent?.text}`);
                this.sendAccessibility();
                return { builder: () => {
                    this.PixelMapBuilder.call(this, this.dragContent?.symbolStyle || this.dragContent?.url, this.dragContent?.text);
                } };
            });
            Grid.onItemDrop((s90, t90, u90, v90) => {
                this.insertItem(t90, u90);
            });
            Grid.onItemDragMove((p90, q90, r90) => this.onDragMoveEvent(p90, q90, r90));
            Grid.onItemDragLeave((n90, o90) => {
                this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_ILLEGAL_AREA);
                this.sendAccessibility();
            });
        }, Grid);
        this.observeComponentCreation2((s89, t89) => {
            ForEach.create();
            const c = (w89, x89) => {
                const y89 = w89;
                {
                    const d = (j90, k90) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.isStartDrag ? DRAG_SPRING : x89 === this.selectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING,
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getShowAreaItemTranslate(x89));
                        Context.animation(null);
                        GridItem.visibility(y89.visibility);
                    };
                    const e = () => {
                        this.observeComponentCreation2(d, GridItem);
                        this.observeComponentCreation2((d90, e90) => {
                            Stack.create();
                            Stack.onHover((i90) => {
                                if (i90) {
                                    this.hoverId = y89.id;
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
                            Stack.onTouch((h90) => {
                                if (this.clickAddBtn || this.clickRemoveBtn) {
                                    return;
                                }
                                if (h90.type === TouchType.Down) {
                                    this.content = y89;
                                    this.isTouchDown = true;
                                }
                                if (h90.type === TouchType.Up || h90.type === TouchType.Cancel) {
                                    this.isTouchDown = false;
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: LONG_TOUCH_SCALE
                                    }, () => {
                                        this.longScaleOnePointTwo = 1;
                                    });
                                }
                            });
                            Stack.id(`edit_grid_item_${x89}`);
                            Stack.onVisibleAreaChange([0.0, 1.0], (f90, g90) => {
                                if (f90) {
                                    if (!this.readFlag && x89 === this.readIndex4EditArea) {
                                        this.pointToNextOne();
                                    }
                                }
                            });
                            Stack.accessibilityGroup(true);
                            Stack.accessibilityLevel(YES);
                            Stack.accessibilityText(this.readFlag ?
                            this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM, `${y89.text ?? ''}`) :
                            this.textAnnouncedForAccessibility);
                            Stack.accessibilityDescription(this.readFlag ?
                            this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DESC) : '');
                        }, Stack);
                        this.observeComponentCreation2((b90, c90) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(y89, DELETE);
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockBuilder.bind(this)(y89);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    e();
                }
            };
            this.forEachUpdateFunction(s89, this.selected, c, (v89) => v89.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
        Column.pop();
    }
    pointToRepeat(l89) {
        this.readFlag = false;
        let m89 = '';
        let n89 = -1;
        if (l89 === ADD) {
            n89 = this.unSelected.findIndex(q89 => q89.id === this.content.id);
            this.readIndex4AddArea = n89;
            m89 = `add_grid_item_${n89}`;
        }
        else {
            n89 = this.selected.findIndex(p89 => p89.id === this.content.id);
            this.readIndex4EditArea = n89;
            m89 = `edit_grid_item_${n89}`;
        }
        this.textAnnouncedForAccessibility = getContext().resourceManager
            .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE);
        let o89 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: m89
        });
        accessibility.sendAccessibilityEvent(o89).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4EditArea = -1;
                this.readIndex4AddArea = -1;
                this.textAnnouncedForAccessibility = '';
            }, ENTER_EXIT_ICON_DURATION);
        });
    }
    insertItem(j89, k89) {
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
        if (k89 !== -1) {
            this.selected.splice(j89, 1);
            this.selected.splice(k89, 0, this.dragContent);
            this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP, Math.floor(k89 / this.colNum) + 1, k89 % this.colNum + 1);
        }
        else {
            this.insertIndex = j89;
            this.textAnnouncedForAccessibility = this.getStringByResource(ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP, Math.floor(j89 / this.colNum) + 1, j89 % this.colNum + 1);
        }
        this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
        this.dragContent.visibility = Visibility.Visible;
        this.calcGridHeight();
        this.readFlag = false;
        this.readIndex4EditArea = this.insertIndex;
    }
    pointToNextOne() {
        let i89 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: `edit_grid_item_${this.readIndex4EditArea}`
        });
        accessibility.sendAccessibilityEvent(i89).then(() => {
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
        this.observeComponentCreation2((g89, h89) => {
            Column.create();
            Column.width('100%');
            Column.height('90%');
        }, Column);
        this.HeaderTitleBuilder.bind(this)();
        this.observeComponentCreation2((e89, f89) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((a89, b89) => {
            Column.create();
            Column.onAreaChange((c89, d89) => {
                this.areaWidth = Number(d89.width);
                this.calcAreaInfo();
            });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((y88, z88) => {
            __Common__.create();
            __Common__.margin({ bottom: MARGIN_EIGHT });
        }, __Common__);
        {
            this.observeComponentCreation2((u88, v88) => {
                if (v88) {
                    let w88 = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, u88, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 1865, col: 11 });
                    ViewPU.create(w88);
                    let b = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.showAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    w88.paramsGenerator_ = b;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(u88, {
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
        this.observeComponentCreation2((q88, r88) => {
            __Common__.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            });
            __Common__.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {});
            Context.animation(null);
            __Common__.margin({ bottom: MARGIN_EIGHT });
            __Common__.onAreaChange((s88, t88) => {
                this.subTitleHeight = Number(t88.height);
            });
        }, __Common__);
        {
            this.observeComponentCreation2((m88, n88) => {
                if (n88) {
                    let o88 = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, m88, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 1874, col: 11 });
                    ViewPU.create(o88);
                    let a = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.addAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    o88.paramsGenerator_ = a;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(m88, {
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
    getStringByResource(j88, ...k88) {
        if (j88) {
            try {
                return getContext(this).resourceManager.getStringByNameSync(j88, ...k88);
            }
            catch (l88) {
                console.error(`Ace SegmentButton getAccessibilityDescription, error: ${l88.toString()}`);
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
