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

import vibrator from '@ohos.vibrator';
import curves from '@ohos.curves';

// import component
import {
  ComposeTitleBar, LengthMetrics, MeasureText, EditableTitleBar,
  EditableLeftIconType, SubHeader, OperationType, SymbolGlyphModifier
} from '@kit.ArkUI';
import { common, EnvironmentCallback } from '@kit.AbilityKit';
import { BusinessError } from '@kit.BasicServicesKit';
import accessibility from '@ohos.accessibility';
import hilog from '@ohos.hilog';

//  declaring Constants
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
// Animation Parameters
const ENTER_EXIT_ICON_DURATION = 200;
const SEND_EVENT_DURATION = 10;
const COMMON_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1); // Curve of entering and exiting the editing state
const DRAG_SPRING = curves.interpolatingSpring(0, 1, 400, 38); // Drag to move and fill curves
const REMOVE_ADD_SPRING = curves.interpolatingSpring(0, 1, 150, 24); // Delete Add Curve
const LONG_TOUCH_SCALE = curves.cubicBezierCurve(0.2, 0, 0.2, 1); // Press and hold the floating curve
// ACCESSIBILITY
const ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE: string = 'gridobjectsortcomponent_accessibility_item_long_press_gesture';
const ACCESSIBILITY_ILLEGAL_AREA: string = 'gridobjectsortcomponent_accessibility_illegal_area';
const ACCESSIBILITY_SELECTED_ITEM_DRAG_START: string =
  'gridobjectsortcomponent_accessibility_selected_item_drag_start';
const ACCESSIBILITY_DOUBLE_CLICK: string =
  'gridobjectsortcomponent_accessibility_single_finger_double_click';
const ACCESSIBILITY_RESIDENT_AREA: string =
  'gridobjectsortcomponent_accessibility_resident_area_edit_state';
const ACCESSIBILITY_SELECTED_ITEM_DESC: string = 'gridobjectsortcomponent_accessibility_selected_item_desc';
const ACCESSIBILITY_SELECTED_ITEM: string = 'gridobjectsortcomponent_accessibility_selected_item';
const ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP: string = 'gridobjectsortcomponent_accessibility_selected_item_drag_stop';
const ACCESSIBILITY_UNSELECTED_ITEM_ADD: string = 'gridobjectsortcomponent_accessibility_unselected_item_add';
const ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC: string =
  'gridobjectsortcomponent_accessibility_unselected_image_item_desc';
const ACCESSIBILITY_UNSELECTED_TEXT_ITEM_DESC: string =
  'gridobjectsortcomponent_accessibility_unselected_text_item_desc';
const ACCESSIBILITY_UNSELECTED_ITEM: string = 'gridobjectsortcomponent_accessibility_unselected_item';
const ACCESSIBILITY_SELECTED_ITEM_DELETE: string = 'gridobjectsortcomponent_accessibility_selected_item_delete';
const ACCESSIBILITY_SELECTED_ITEM_DRAG_MOVING: string =
  'gridobjectsortcomponent_accessibility_selected_item_drag_moving';
const ACCESSIBILITY_DELETED: string = 'gridobjectsortcomponent_accessibility_deleted';
const ACCESSIBILITY_UNSELECTED_BUTTON: string = 'gridobjectsortcomponent_accessibility_unselected_button';
const EDIT_TITLE_BAR_ID: string = 'EditTitleBar';
const ADD_TITLE_BAR_ID: string = 'AddTitleBar';
const ADD_GRID_FIRST_ITEM_ID: string = 'add_grid_item_0';
const YES: string = 'yes';
const NO: string = 'no';
const ADD: string = 'add';
const EDIT: string = 'edit';
const DELETE = 'delete';

// declaring interface, enum, class
export interface GridObjectSortComponentItem {
  id: number | string;
  text: ResourceStr;
  selected: boolean;
  order: number;
  url?: ResourceStr;
  symbolStyle?:SymbolGlyphModifier;
  visibility?: Visibility;
}

export interface GridObjectSortComponentOptions {
  type?: GridObjectSortComponentType;
  imageSize?: number | Resource;
  normalTitle?: ResourceStr;
  editTitle?: ResourceStr;
  showAreaTitle?: ResourceStr;
  addAreaTitle?: ResourceStr;
}

export enum GridObjectSortComponentType {
  IMAGE_TEXT = 'image_text',
  TEXT = 'text'
}

interface PositionXY {
  x: number;
  y: number;
}

@Component
export struct GridObjectSortComponent {
  // component configuration data
  @Prop options: GridObjectSortComponentOptions = {};
  // data
  dataList: GridObjectSortComponentItem[] = [];
  // Drag and drop edit data,  selected === true
  @State selected: GridObjectSortComponentItem[] = [];
  // add data, selected === false
  @State unSelected: GridObjectSortComponentItem[] = [];
  // copy data
  @State copySelected: GridObjectSortComponentItem[] = [];
  @State copyUnSelected: GridObjectSortComponentItem[] = [];
  // Current data when touched
  @State content: GridObjectSortComponentItem = {
    id: '',
    text: '',
    selected: false,
    order: 0
  };
  @State dragContent: GridObjectSortComponentItem = {
    id: '',
    text: '',
    selected: false,
    order: 0
  };
  @State dragContentIndex: number = -1;
  @State hoverId: number | string = '';
  // component state : edit === true   unedited === false
  @State @Watch('onGridComStateChange') gridComState: boolean = false;
  @State menuSwitch: boolean = false;
  // component width
  @State areaWidth: number = 0;
  // component item width
  @State blockWidth: number = 0;
  // component item height
  @State blockHeight: number = 0;
  // controlled zoom animation
  @State longScaleOnePointTwo: number = 1;
  @State scaleGridItemNinetyPercent: number = 1;
  @State reboundSize: number = 1;
  @State scaleIcon: number = 1;
  @State addIconShow: boolean = false;
  @State scaleAddIcon: number = 0;
  // whether to start dragging
  @State isStartDrag: boolean = false;
  @State insertIndex: number = -1;
  @State itemIndex: number = 0;
  @State editGridDataLength: number = -1;
  @State isTouchDown: boolean = false;
  @State addItemMoveX: number = 0;
  @State addItemMoveY: number = 0;
  @State editItemMoveX: number = 0;
  @State editItemMoveY: number = 0;
  @State unSelectedIndex: number = 0;
  @State clickAddBtn: boolean = false;
  @State selectedIndex: number = -1;
  @State clickRemoveBtn: boolean = false;
  @State addAreaLongPressGesture: boolean = false;
  @State arraySelectIsChange: number = 0;
  @State arrayUnSelectIsChange: number = 0;
  @State textItemEditWidth: number = 0;
  @State textItemEditHeight: number = 0;
  @State imageItemWidth: number = 0;
  @State saveClick: boolean = false;
  @State imageTextAddIconShow: boolean = false;
  @State imageTextRemoveIconShow: boolean = false;
  @State firstIn: boolean = true;
  @State @Watch('calcAreaInfo') fontSizeScale: number | undefined = 1;
  @State fontWeightScale: number | undefined = 1;
  @State customColumns: string = '1fr 1fr 1fr 1fr';
  @State editGridHeight: number = 0;
  @State addGridHeight: number = 0;
  @State subTitleHeight: number = 0;
  @State isOpenAccessibility: boolean = accessibility.isScreenReaderOpenSync();
  private callbackId: number | undefined = undefined;
  // current column, text: 4 column  , image_text: 3 column
  private colNum: number = COL_IMAGE_TEXT;
  private vibrationDone: boolean = false;
  private touchDown: Resource = $r('sys.color.ohos_id_color_click_effect');
  private touchBorderRadius: Resource = $r('sys.float.ohos_id_corner_radius_clicked');
  private hoverBackgroundColor: Resource = $r('sys.color.ohos_id_color_hover');
  private imageText: boolean = false;

  onSave?: (select: GridObjectSortComponentItem[], unselect: GridObjectSortComponentItem[]) => void;
  onCancel?: () => void;
  isFollowingSystemFontScale: boolean = false;
  maxAppFontScale: number = 1;

  bundleName: string = '';
  @State readFlag: boolean = true;
  @State readIndex4AddArea: number = -1;
  @State readIndex4EditArea: number = -1;
  @State isPointToAddTitleBarEditButton: boolean = false;
  @State isPointToEditTitleBarSaveButton: boolean = false;
  preTextAnnouncedForAccessibility: string = '';
  textAnnouncedForAccessibility: string = '';

  // component rendering
  aboutToAppear() {
    this.dataList.length = 50;
    this.selected = this.dataList && this.deduplicate(this.dataList).filter(val => val.selected).sort(this.sortBy());
    this.unSelected = this.dataList && this.deduplicate(this.dataList).filter(val =>!val.selected).sort(this.sortBy());
    this.copySelected = this.selected.slice();
    this.copyUnSelected = this.unSelected.slice();
    this.editGridDataLength = this.selected.length;
    this.imageText = this.options.type === GridObjectSortComponentType.IMAGE_TEXT;
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxAppFontScale = uiContent.getMaxFontScale();
      this.fontSizeScale = this.decideFontScale(uiContent);
      this.fontWeightScale =
        (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontWeightScale ?? DEFAULT_FONT_WEIGHT_SCALE;
    } catch (exception) {
      let code = (exception as BusinessError).code;
      let message = (exception as BusinessError).message;
      hilog.error(0x3900, 'Ace',
        `GridObjectSortComponent Faild to init fontsizescale info, code:${code}, message: ${message}`);
    }
    try {
      this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
    } catch (paramError) {
      let code = (paramError as BusinessError).code;
      let message = (paramError as BusinessError).message;
      hilog.error(0x3900, 'Ace',
        `GridObjectSortComponent Faild to get environment param error: ${code}, ${message}`);
    }
    this.calcGridHeight();
    setTimeout(() => {
      this.firstIn = false;
    }, 500);
    this.bundleName = (getContext(this) as common.UIAbilityContext)?.abilityInfo?.bundleName;
    accessibility.on('screenReaderStateChange', (state: boolean) => {
      // 上面的state  就是无障碍的状态
      this.isOpenAccessibility = state;
    });
  }

  // get adaptive for symbol font size
  getAdaptiveSymbolFontSize(): string {
    let fontScale : number | undefined = this.fontSizeScale;
    if (!this.isFollowingSystemFontScale || fontScale === undefined) {
      fontScale = MIN_FONT_SCALE;
    }
    fontScale = Math.min(MIN_SYMBOL_FONT_SCALE, fontScale);
    fontScale = Math.max(fontScale, MIN_FONT_SCALE);
    return (fontScale * SYMBOL_SIZE_12FP).toString() + 'vp';
  }

  // translate option imageSize to symbol fontSize
  getSymbolFontSizeFrom(imageSize?: number | Resource | undefined) : string | Resource {
    if (imageSize === undefined) {
      return SYMBOL_DEFAULT;
    }
    if (typeof imageSize === 'number') {
      return (imageSize as number).toString() + 'vp';
    }
    return imageSize as Resource;
  }


  calcTextItemEditHeight() {
    let sizeOptions: SizeOptions = MeasureText.measureTextSize({
      textContent: this.dataList[0]?.text ?? '',
      fontSize: `${(LengthMetrics.resource($r('sys.float.ohos_id_text_size_button3'))?.value ??
        DEFAULT_TEXT_SIZE) * (this.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE)}vp`,
      overflow: TextOverflow.Ellipsis,
      maxLines: TEXT_MAX_LINES
    });
    this.textItemEditHeight = this.fontSizeScale === DEFAULT_FONT_SIZE_SCALE ?
      GRID_ITEM_HEIGHT_TEXT : px2vp(sizeOptions.height as number);
    this.textItemEditHeight = this.textItemEditHeight + PADDING_EIGHT * 2;
  }

  private envCallback: EnvironmentCallback = {
    onConfigurationUpdated: (config) => {
      let uiContent: UIContext = this.getUIContext();
      this.fontSizeScale = this.decideFontScale(uiContent);
      this.fontWeightScale = config.fontWeightScale;
    },
    onMemoryLevel: (level) => {}
  }

  decideFontScale(uiContent: UIContext): number {
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    let systemFontScale: number | undefined =
      (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE;
    return Math.min(systemFontScale, this.maxAppFontScale, MAX_FONT_SCALE);
  }

  private calcColNum() {
    if (this.imageText || (this.fontSizeScale && this.fontSizeScale > DEFAULT_FONT_SIZE_SCALE)) {
      this.customColumns = GRID_COL_3;
      this.colNum = COL_IMAGE_TEXT;
    } else {
      this.customColumns = GRID_COL_4;
      this.colNum = COL_TEXT;
    }
  }

  // component disappear
  aboutToDisappear() {
    animateTo({
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

  // Array deduplication
  deduplicate(arr: GridObjectSortComponentItem[]) {
    const result: GridObjectSortComponentItem[] = [];
    arr.forEach(item => {
      if (!result.some(x => x.id === item.id)) {
        result.push(item);
      }
    });
    return result;
  }

  // Listen to the change of the editing status of the component.
  onGridComStateChange(): void {
    this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
    if (!this.imageText) {
      this.blockHeight = this.gridComState ?
        this.textItemEditHeight + EDIT_BLOCK_TEXT_ITEM_SAFE_MARGIN :
        this.textItemEditHeight + DEFAULT_BLOCK_TEXT_ITEM_SAFE_MARGIN;
    }
  }

  sortBy() {
    return (a: GridObjectSortComponentItem, b: GridObjectSortComponentItem) => {
      return a.order - b.order;
    };
  }

  // cancel edit function
  cancelEdit(): void {
    if (this.isStartDrag || this.clickAddBtn || this.clickRemoveBtn) {
      return;
    }
    animateTo({
      duration: ENTER_EXIT_ICON_DURATION,
      curve: LONG_TOUCH_SCALE
    }, () => {
      this.longScaleOnePointTwo = 1;
    })
    animateTo({
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

  // Enter edit function
  goEdit(): void {
    animateTo({
      duration: ENTER_EXIT_ICON_DURATION,
      curve: COMMON_BEZIER,
    }, () => {
      this.gridComState = true;
    });
    this.menuSwitch = true;
    this.isPointToEditTitleBarSaveButton = true;
    this.calcGridHeight();
  }

  pointToEditTitleBarSaveButton(): void {
    if (this.isPointToEditTitleBarSaveButton) {
      let editableTittleBarUniqueId =
        this.getUIContext().getFrameNodeById(EDIT_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
      let eventInfo: accessibility.EventInfo = ({
        type: 'requestFocusForAccessibility',
        bundleName: this.bundleName,
        triggerAction: 'common',
        customId: `ImageMenuItem_${editableTittleBarUniqueId}_0`
      });
      accessibility.sendAccessibilityEvent(eventInfo).then(() => {
        setTimeout(()=>{
          this.isPointToEditTitleBarSaveButton = false;
        }, ENTER_EXIT_ICON_DURATION);
      });
    }
  }

  // save data
  onSaveEdit(): void {
    if (this.isStartDrag) {
      return;
    }
    animateTo({
      duration: ENTER_EXIT_ICON_DURATION,
      curve: LONG_TOUCH_SCALE
    }, () => {
      this.longScaleOnePointTwo = 1;
    })
    this.editGridDataLength = this.selected.length;
    animateTo({
      duration: ENTER_EXIT_ICON_DURATION,
      curve: COMMON_BEZIER,
    }, () => {
      this.gridComState = false;
      this.copySelected = this.selected.slice();
      this.copyUnSelected = this.unSelected.slice();
      const selected = this.getNewData(this.selected, true, 0);
      const unSelected = this.getNewData(this.unSelected, false, this.selected.length);
      this.selected = selected;
      this.unSelected = unSelected;
      this.calcGridHeight();
      this.onSave && this.onSave(selected, unSelected);
    });
    setTimeout(() => {
      this.saveClick = false;
    }, ENTER_EXIT_ICON_DURATION);
    this.menuSwitch = false;
    this.isPointToAddTitleBarEditButton = true;
  }

  pointToAddTitleBarEditButton(): void {
    if (this.isPointToAddTitleBarEditButton) {
      let composeTittleBarUniqueId =
        this.getUIContext()?.getFrameNodeById(ADD_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
      let eventInfo: accessibility.EventInfo = ({
        type: 'requestFocusForAccessibilityNotInterrupt',
        bundleName: this.bundleName,
        triggerAction: 'common',
        customId: `ComposeTitleBar_ImageMenuItem_${composeTittleBarUniqueId}_0`
      });
      setTimeout(() => {
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          setTimeout(() => {
            this.isPointToAddTitleBarEditButton = false;
          }, ENTER_EXIT_ICON_DURATION);
        });
      }, SEND_EVENT_DURATION);
    }
  }

  // Drag and move triggering event
  onDragMoveEvent(event: ItemDragInfo, itemIndex: number, insertIndex: number): void {
    if (!this.gridComState || (event.x < this.blockWidth / 3 && event.y < this.blockHeight / 3)) {
      return;
    }
    let targetIndex: number = insertIndex;
    if (targetIndex < 0) {
      targetIndex = this.selected.length - 1;
    } else {
      this.textAnnouncedForAccessibility = this.getStringByResourceToken(
        ACCESSIBILITY_SELECTED_ITEM_DRAG_MOVING,
        Math.floor(insertIndex / this.colNum) + 1,
        insertIndex % this.colNum + 1
      );
    }
    if (this.dragContent.visibility !== Visibility.Hidden) {
      this.dragContent.visibility = Visibility.Hidden;
    }
    if (this.insertIndex !== insertIndex || itemIndex !== insertIndex) {
      this.sendAccessibility();
    }
    this.insertIndex = insertIndex;
  }

  sendAccessibility(): void {
    if (this.preTextAnnouncedForAccessibility !== this.textAnnouncedForAccessibility) {
      let eventInfo: accessibility.EventInfo = ({
        type: 'announceForAccessibility', // 表示主动播报的事件。
        bundleName: this.bundleName, // 目标应用名；不可缺省。
        triggerAction: 'common', // 表示没有特定操作，用于主动聚焦、主动播报等场景。
        textAnnouncedForAccessibility: this.textAnnouncedForAccessibility // 主动播报的内容。
      });
      accessibility.sendAccessibilityEvent(eventInfo);
      this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
    }
  }

  // delete Editing an Area Item
  handleDeleteClick(content: GridObjectSortComponentItem): void {
    if (this.clickAddBtn || this.clickRemoveBtn) {
      return;
    }
    this.clickRemoveBtn = true;
    this.scaleIcon = 0;
    this.arraySelectIsChange = 1;
    let currentIndex = this.selected.findIndex(val => val.id === content.id);
    this.content = content;
    this.selectedIndex = currentIndex;
    this.calcGridHeight();
    animateTo({curve: REMOVE_ADD_SPRING, onFinish: () => {
      this.scaleIcon = 1;
      this.selected.splice(currentIndex, 1);
      this.unSelected.unshift(content);
      this.calcGridHeight();
      this.editGridDataLength = this.editGridDataLength - 1;
      this.editItemMoveX = 0;
      this.editItemMoveY = 0;
      this.arraySelectIsChange = 2;
      this.clickRemoveBtn = false;
      this.readFlag = false;
      // 播报区域为添加域的第1个，index为0
      this.readIndex4AddArea = 0;
      this.textAnnouncedForAccessibility = this.getStringByResourceToken(
        ACCESSIBILITY_DELETED,
        this.getAccessibilityText(this.content?.text ?? ' ')
      );
    } }, () => {
      let addItemGridPosition = this.getAddItemGridPosition();
      this.editItemMoveX = addItemGridPosition.x;
      this.editItemMoveY = addItemGridPosition.y;
    });
  }

  pointToAddArea(): void {
    let eventInfo: accessibility.EventInfo = ({
      type: 'requestFocusForAccessibility',
      bundleName: this.bundleName,
      triggerAction: 'common',
      customId: ADD_GRID_FIRST_ITEM_ID
    });
    accessibility.sendAccessibilityEvent(eventInfo).then(() => {
      setTimeout(() => {
        this.readFlag = true;
        this.readIndex4AddArea = -1;
      }, ENTER_EXIT_ICON_DURATION
      );
    });
  }

  getNewData(data: GridObjectSortComponentItem[],
    state: boolean, startIndex: number): GridObjectSortComponentItem[] {
    return data.map((val, index) => {
      val.selected = state;
      val.order = startIndex + index;
      val.visibility = Visibility.Visible;
      return val;
    });
  }

  // Obtains the width of each girdItem.
  getBlockWidth(): number {
    const blockWidth: number = (this.areaWidth - 32) / this.colNum;
    return blockWidth;
  }

  calcGridHeight(): void {
    this.editGridHeight = this.getGridHeight(this.selected, EDIT);
    this.addGridHeight = this.getGridHeight(this.unSelected);
  }

  // calculated altitude
  getGridHeight(data: GridObjectSortComponentItem[], state?: string): number {
    let height: number = 0;
    let selectLen: number = data.length;
    data.forEach(item => {
      if (item.visibility === Visibility.Hidden) {
        selectLen = selectLen - 1;
      }
    });
    let addRow: number = 0;
    let lastColumn: boolean = selectLen % this.colNum === 0;
    if (this.clickAddBtn && lastColumn) {
      addRow = 1;
    } else if (this.isStartDrag && lastColumn && state) {
      addRow = 1;
    } else if (this.clickRemoveBtn && lastColumn && !state) {
      addRow = 1;
    } else {
      addRow = 0;
    }
    let rowNumber: number = Math.ceil(selectLen / this.colNum) + addRow;
    height = this.blockHeight * rowNumber;
    if (selectLen === 0) {
      height = 0;
    }
    return height;
  }

  // Display area icon in image_text mode
  imageTextRemoveIcon(select: GridObjectSortComponentItem): Resource {
    const clickRemoveIcon: boolean = this.clickRemoveBtn && this.content.id === select.id;
    const icon = clickRemoveIcon ?
    $r('sys.symbol.plus_circle_fill') : $r('sys.symbol.minus_circle_fill');
    return icon;
  }

  // Adding a Region Icon in image_text Mode
  imageTextAddIcon(select: GridObjectSortComponentItem): Resource {
    const clickAddIcon: boolean = this.clickAddBtn && this.content.id === select.id && this.gridComState;
    const icon = clickAddIcon ?
    $r('sys.symbol.minus_circle_fill') : $r('sys.symbol.plus_circle_fill');
    return icon;
  }

  // Displaying and hiding area icons in image_text mode
  imageTextAddIconVisible(select: GridObjectSortComponentItem): Visibility {
    const iconHideShow: boolean = this.clickAddBtn && this.content.id === select.id && !this.gridComState;
    const visible = iconHideShow ? Visibility.Hidden : Visibility.Visible;
    return visible;
  }

  // Drag position calculation in the editing area
  getCoodXY(index: number): PositionXY {
    let x: number = 0;
    let y: number = 0;
    const gridCol: number = this.colNum;
    const lastCol: number = Math.trunc(index % gridCol);
    if (index >= this.dragContentIndex) {
      if (index <= this.insertIndex && index !== this.dragContentIndex) {
        // item  newline
        if (lastCol === 0) {
          x = x + this.blockWidth * (gridCol - 1);
          y = y - this.blockHeight;
        } else {
          // left move
          x = x - this.blockWidth;
        }
      }
    } else {
      if (index >= this.insertIndex) {
        // item  newline
        if (lastCol === gridCol - 1) {
          x = x - this.blockWidth * (gridCol - 1);
          y = y + this.blockHeight;
        } else {
          // right move
          x = x + this.blockWidth;
        }
      }
    }
    if (!this.isStartDrag) {
      x = 0;
      y = 0;
    }
    return { x, y };
  }

  // Position calculation when an item is deleted, Displacement to the first position. (top => bottom)
  getAddItemGridPosition(): PositionXY {
    const len: number = this.selected.length;
    const col: number = this.colNum;
    const removeCol: number = (this.selectedIndex + 1) % col;
    const currentLine: number = Math.ceil((this.selectedIndex + 1) / col);
    const totalRows: number = Math.ceil(len / col);
    const bool: boolean = this.imageText;
    let xNew: number = 0;
    if (removeCol === 0) {
      xNew = bool || (this.fontSizeScale && this.fontSizeScale > 1) ? -this.blockWidth * 2 : -this.blockWidth * 3;
    } else {
      xNew = -this.blockWidth * (removeCol - 1);
    }
    let subTitleHeight: number = SUBTITLE_HEIGHT;
    let yNew: number = 0;
    const removeNumY: number = totalRows - currentLine;
    const minusLine: number = len % col;
    const line: number = minusLine === 1 ? removeNumY : removeNumY + 1;
    if (this.fontSizeScale && this.fontSizeScale > 1) {
      subTitleHeight = this.subTitleHeight;
    }
    yNew = line * this.blockHeight + subTitleHeight;
    return {
      x: xNew,
      y: yNew
    };
  }

  // When an item is deleted, the filling position of other items is calculated.
  getCoveringGridPosition(index: number): PositionXY {
    let xNew: number = 0;
    let yNew: number = 0;
    if (index > this.selectedIndex && this.arraySelectIsChange !== 2) {
      xNew = index % this.colNum === 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
      yNew = index % this.colNum === 0 ? -this.blockHeight : 0;
    }
    return {
      x: xNew,
      y: yNew
    };
  }

  // Position calculation when adding an item. (bottom => top)
  getEditItemGridPosition(data: GridObjectSortComponentItem[], removeIndex: number): PositionXY {
    const len: number = data.length;
    const col: number = this.colNum;
    const insertCol: number = Math.trunc(len % col);
    const removeCol: number = Math.trunc(removeIndex % col);
    let xNew: number = Math.abs(insertCol - removeCol) * this.blockWidth;

    if (insertCol < removeCol) {
      xNew = -xNew;
    } else if (insertCol > removeCol) {
      xNew = xNew;
    } else {
      xNew = 0;
    }

    let yNew: number = 0;
    let itemHeight: number = 0;
    let removeRow: number = Math.trunc(removeIndex / this.colNum);
    let subTitleHeight: number = SUBTITLE_HEIGHT;
    const textShowAreaEditItem: boolean = !this.imageText && this.gridComState && removeIndex > 3;
    if (textShowAreaEditItem) {
      itemHeight = (removeRow + 1) * (this.blockHeight - 8) + 8;
    } else {
      itemHeight = (removeRow + 1) * this.blockHeight;
    }
    if (this.fontSizeScale && this.fontSizeScale > 1) {
      subTitleHeight = this.subTitleHeight;
    }
    yNew = itemHeight + subTitleHeight;
    return {
      x: xNew,
      y: yNew
    };
  }

  // When an item is added, the filling of other items in the addition area is calculated.
  getCoveringGridPositionBottom(index: number): PositionXY {
    let xNew: number = 0;
    let yNew: number = 0;
    const lastCol: boolean = index % this.colNum === 0;
    const textShowAreaItemHeight: number =
      this.gridComState && !this.imageText ? -this.blockHeight + 8 : -this.blockHeight;
    if (index > this.unSelectedIndex && this.arrayUnSelectIsChange !== 2) {
      xNew = lastCol ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
      yNew = lastCol ? textShowAreaItemHeight : 0;
    }
    return {
      x: xNew,
      y: yNew
    };
  }

  // When an item is deleted, other items in the addition area are moved rightwards.
  getAddItemRightMove(index: number): PositionXY {
    let x: number = this.blockWidth;
    let y: number = 0;
    let lastCol: boolean = (index + 1) % this.colNum === 0;
    if (lastCol) {
      x = -this.blockWidth * (this.colNum - 1);
      y = this.imageText ? this.blockHeight : this.blockHeight - 8;
    }
    return { x, y };
  }

  // Display area movement function
  getShowAreaItemTranslate(index: number): PositionXY {
    // Position when dragging
    if (this.isStartDrag) {
      let coodXY = this.getCoodXY(index);
      return {
        x: coodXY.x,
        y: coodXY.y
      };
    }

    // Position when remove item
    if (!this.isStartDrag && index === this.selectedIndex) {
      return {
        x: this.editItemMoveX,
        y: this.editItemMoveY
      };
    }

    // Filling position
    if (!this.isStartDrag && index !== this.selectedIndex && this.clickRemoveBtn) {
      let coveringGridPosition = this.getCoveringGridPosition(index);
      return {
        x: coveringGridPosition.x,
        y: coveringGridPosition.y
      };
    }

    return { x: 0, y: 0 };
  }

  // Add area movement function
  getAddAreaItemTranslate(index: number): PositionXY {
    // When an item is removed, the added area is moved rightward.
    if (this.clickRemoveBtn) {
      let addItemRightMove = this.getAddItemRightMove(index);
      return {
        x: addItemRightMove.x,
        y: addItemRightMove.y
      };
    }

    // Move the position when adding an item.
    if (!this.clickRemoveBtn && index === this.unSelectedIndex) {
      return {
        x: this.addItemMoveX,
        y: -this.addItemMoveY
      };
    }

    // Filling position when adding
    if (!this.clickRemoveBtn && index !== this.unSelectedIndex && this.clickAddBtn) {
      let coveringGridPositionBottom = this.getCoveringGridPositionBottom(index);
      return {
        x: coveringGridPositionBottom.x,
        y: coveringGridPositionBottom.y
      };
    }

    return { x: 0, y: 0 };
  }

  @Builder
  PixelMapBuilder(url: ResourceStr | SymbolGlyphModifier | undefined, text: ResourceStr) {
    Stack({ alignContent: Alignment.Center }) {
      if (this.imageText) {
        Column() {
          if (url === undefined) {
            SymbolGlyph()
              .draggable(false)
              .height(this.options.imageSize || SYMBOL_DEFAULT)
              .width(this.options.imageSize || SYMBOL_DEFAULT)
              .fontSize(this.getSymbolFontSizeFrom(this.options.imageSize))
          } else if (url instanceof SymbolGlyphModifier) {
            SymbolGlyph()
              .draggable(false)
              .height(this.options.imageSize || SYMBOL_DEFAULT)
              .width(this.options.imageSize || SYMBOL_DEFAULT)
              .attributeModifier(url)
              .fontSize(this.getSymbolFontSizeFrom(this.options.imageSize))
              .symbolEffect(new SymbolEffect(), false)
          } else {
            Image(url)
              .draggable(false)
              .height(this.options.imageSize || IMAGE_DEFAULT)
              .width(this.options.imageSize || IMAGE_DEFAULT)
          }
          Text(text)
            .textAlign(TextAlign.Center)
            .fontSize($r('sys.float.ohos_id_text_size_button3'))
            .margin({ top: 2 })
            .maxLines(TEXT_MAX_LINES)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .minFontScale(MIN_FONT_SCALE)
            .maxFontScale(this.fontSizeScale)

          SymbolGlyph($r('sys.symbol.minus_circle_fill'))
            .fontSize(SYMBOL_SIZE_24VP)
            .fontWeight(SYMBOL_WEIGHT)
            .draggable(false)
            .fontColor([$r('sys.color.ohos_id_color_secondary')])
            .width(ICON_SIZE)
            .height(ICON_SIZE)
            .position({
              x: this.blockWidth - 40,
              y: -MARGIN_EIGHT
            })
        }
        .alignItems(HorizontalAlign.Center)
        .justifyContent(FlexAlign.Center)
        .width(this.imageItemWidth)
        .height(this.imageItemWidth)
        .padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT })
        .backgroundColor(this.touchDown)
        .borderRadius(this.touchBorderRadius)
        .scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo })
      } else {
        Row() {
          Text(text)
            .fontColor($r('sys.color.ohos_id_color_text_primary'))
            .fontSize($r('sys.float.ohos_id_text_size_button3'))
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .textAlign(TextAlign.Center)
            .maxLines(TEXT_MAX_LINES)
            .minFontScale(MIN_FONT_SCALE)
            .maxFontScale(this.fontSizeScale)

          SymbolGlyph($r('sys.symbol.minus_circle_fill'))
            .fontSize(SYMBOL_SIZE_24VP)
            .fontWeight(SYMBOL_WEIGHT)
            .draggable(false)
            .fontColor([$r('sys.color.ohos_id_color_secondary')])
            .width(ICON_SIZE)
            .height(ICON_SIZE)
            .position({
              x: this.blockWidth - 52, // gridItem-padding: 16，row-padding: 12，icon: 24 - 8 = 16
              y: -MARGIN_EIGHT
            })
        }
        .borderRadius(50)
        .padding({
          left: TEXT_PADDING_LEFT_RIGHT,
          right: TEXT_PADDING_LEFT_RIGHT,
        })
        .scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo })
        .alignItems(VerticalAlign.Center)
        .justifyContent(FlexAlign.Center)
        .backgroundColor($r('sys.color.ohos_id_color_button_normal'))
        .width(this.textItemEditWidth)
        .height(this.textItemEditHeight)
      }
    }
    .clip(false)
    .height(this.blockHeight * 1.5)
    .width(this.blockWidth * 1.2)
  }

  @Builder
  HeaderTitleBuilder() {
    ComposeTitleBar({
      title: this.options.normalTitle || $r('sys.string.ohos_grid_edit_title_chanel'),
      menuItems: [{
        value: $r('sys.media.ohos_ic_public_edit'),
        symbolStyle: (new SymbolGlyphModifier($r('sys.symbol.square_and_pencil'))),
        isEnabled: true,
        label: $r('sys.string.gridobjectsortcomponent_accessibility_header_edit_button'),
        accessibilityText: $r('sys.string.gridobjectsortcomponent_accessibility_header_edit_button'),
        action: () => {
          this.goEdit();
        }
      }]
    })
      .id(ADD_TITLE_BAR_ID)
      .visibility(!this.menuSwitch ? Visibility.Visible : Visibility.None)
      .onVisibleAreaChange([0.0, 1.0], (isVisible: boolean, currentRatio: number) => {
        if (isVisible) {
          this.pointToAddTitleBarEditButton();
        } else {
          if (this.isPointToEditTitleBarSaveButton) {
            let eventInfo: accessibility.EventInfo = ({
              type: 'announceForAccessibility', // 表示主动播报的事件。
              bundleName: this.bundleName, // 目标应用名；不可缺省。
              triggerAction: 'common', // 表示没有特定操作，用于主动聚焦、主动播报等场景。
              textAnnouncedForAccessibility: getContext().resourceManager
                .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE) // 主动播报的内容。
            });
            accessibility.sendAccessibilityEvent(eventInfo);
          }
        }
      })
    EditableTitleBar({
      leftIconStyle: EditableLeftIconType.Cancel,
      isSaveIconRequired: false,
      menuItems: [{
        value: $r('sys.symbol.checkmark'),
        label: $r('sys.string.gridobjectsortcomponent_accessibility_complete_button'),
        accessibilityText: $r('sys.string.gridobjectsortcomponent_accessibility_complete_button'),
        action: () => {
          this.saveClick = true;
          this.onSaveEdit();
        }
      }],
      title: this.options.editTitle || $r('sys.string.ohos_grid_edit_title_edit'),
      onCancel: () => {
        this.cancelEdit();
      },
    })
      .id(EDIT_TITLE_BAR_ID)
      .visibility(this.menuSwitch ? Visibility.Visible : Visibility.None)
      .onVisibleAreaChange([0.0, 1.0], (isVisible: boolean, currentRatio: number) => {
        if (isVisible) {
          this.pointToEditTitleBarSaveButton();
        }
      })
  }

  @Builder
  ImageTextBuilder(select: GridObjectSortComponentItem, type: string) {
    Column() {
      Column() {
        if (select.symbolStyle !== undefined) {
          SymbolGlyph()
            .draggable(false)
            .attributeModifier(select.symbolStyle)
            .fontSize(this.getSymbolFontSizeFrom(this.options.imageSize))
            .symbolEffect(new SymbolEffect(), false)
        } else {
          if (select.url === undefined) {
            SymbolGlyph()
              .draggable(false)
              .fontSize(this.getSymbolFontSizeFrom(this.options.imageSize))
          } else {
            Image(select.url)
              .draggable(false)
              .height(this.options.imageSize || IMAGE_DEFAULT)
              .width((this.options.imageSize || IMAGE_DEFAULT))
          }
        }
        Text(select.text)
          .textAlign(TextAlign.Center)
          .fontSize($r('sys.float.ohos_id_text_size_button3'))
          .margin({ top: 2 })
          .maxLines(TEXT_MAX_LINES)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .minFontScale(MIN_FONT_SCALE)
          .maxFontScale(this.fontSizeScale)
          .padding({
            top: PADDING_EIGHT,
            bottom: PADDING_EIGHT
          })

        SymbolGlyph(this.imageTextAddIcon(select))
          .fontSize(SYMBOL_SIZE_24VP)
          .fontWeight(SYMBOL_WEIGHT)
          .draggable(false)
          .visibility(type === 'add' ? this.imageTextAddIconVisible(select) : Visibility.Hidden)
          .fontColor([$r('sys.color.ohos_id_color_secondary')])
          .width(ICON_SIZE)
          .height(ICON_SIZE)
          .position({
            x: this.blockWidth - 40,
            y: -MARGIN_EIGHT
          })
          .onClick(() => this.handleAddIconClick(select))
          .accessibilityLevel(YES)
          .accessibilityText(
            this.getStringByResourceToken(
              ACCESSIBILITY_UNSELECTED_BUTTON, this.getAccessibilityText(select.text))
          )

        SymbolGlyph(this.imageTextRemoveIcon(select))
          .fontSize(SYMBOL_SIZE_24VP)
          .fontWeight(SYMBOL_WEIGHT)
          .draggable(false)
          .fontColor([$r('sys.color.ohos_id_color_secondary')])
          .visibility(type === 'delete' && this.gridComState ? Visibility.Visible :
          Visibility.Hidden)
          .width(ICON_SIZE)
          .height(ICON_SIZE)
          .position({
            x: this.blockWidth - 40,
            y: -MARGIN_EIGHT
          })
          .onClick(() => this.handleDeleteClick(select))
          .accessibilityLevel(YES)
          .accessibilityText(
            this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DELETE, this.getAccessibilityText(select.text))
          )
      }
      .alignItems(HorizontalAlign.Center)
      .justifyContent(FlexAlign.Center)
      .width('100%')
      .height(this.imageItemWidth)
      .padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT })
      .borderRadius((this.isTouchDown && select.id === this.content.id) ||
        select.id === this.hoverId ? this.touchBorderRadius : 0)
      .backgroundColor(
        this.isTouchDown && select.id === this.content.id
          ? this.touchDown : select.id === this.hoverId ? this.hoverBackgroundColor : ''
      )
      .scale(select.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {})
    }
    .padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT })
    .width('100%')
  }

  handleAddIconClick(content: GridObjectSortComponentItem): void {
    if (this.clickAddBtn || this.clickRemoveBtn) {
      return;
    }
    this.scaleIcon = 0;
    this.content = content;
    const index = this.unSelected.findIndex(i => i.id === content.id);
    this.editGridDataLength = this.selected.length + 1;
    const endPosition = this.getEditItemGridPosition(this.selected, index);
    this.unSelectedIndex = index;
    this.arrayUnSelectIsChange = 1;
    this.clickAddBtn = true;
    this.calcGridHeight();
    animateTo({
      curve: REMOVE_ADD_SPRING,
      onFinish: () => {
        if (!this.selected.some(val => val.id === content.id)) {
          this.arrayUnSelectIsChange = 2;
          this.scaleIcon = 1;
          this.selected.push(content);
          this.unSelected.splice(index, 1);
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
      this.addItemMoveX = endPosition.x;
      this.addItemMoveY = endPosition.y;
    })
    this.readFlag = false;
    this.readIndex4EditArea = this.editGridDataLength - 1;
    this.textAnnouncedForAccessibility = this.getStringByResourceToken(
      ACCESSIBILITY_UNSELECTED_ITEM_ADD,
      this.getAccessibilityText(this.content?.text ?? ''),
      Math.floor(this.readIndex4EditArea / this.colNum) + 1,
      this.readIndex4EditArea % this.colNum + 1
    );
  }

  // 文本模式拖动排序区域item
  @Builder
  TextBlockBuilder(select: GridObjectSortComponentItem) {
    Stack() {
      Row() {
      }
      .borderRadius(50)
      .width(this.clickRemoveBtn && select.id === this.content.id ?
        this.textItemEditWidth + 8 : this.textItemEditWidth)
      .translate(this.gridComState ? this.clickRemoveBtn &&
        select.id === this.content.id ? { x: 0 } : { x: -4 } : { x: 0 })
      .height('100%')
      .animation(!this.firstIn ? {
        duration: ENTER_EXIT_ICON_DURATION,
        curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
      } : { duration: 0 })
      .backgroundColor($r('sys.color.ohos_id_color_button_normal'))

      Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        SymbolGlyph($r('sys.symbol.plus'))
          .fontSize(this.getAdaptiveSymbolFontSize())
          .draggable(false)
          .fontColor([$r('sys.color.ohos_id_color_text_secondary')])
          .visibility(this.clickRemoveBtn && select.id === this.content.id ? Visibility.Visible : Visibility.None)
          .transition({ type: TransitionType.All, scale: { x: 0, y: 0, } })
          .margin({ right: 4 })
          .animation({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER
          })

        Text(select.text)
          .fontColor($r('sys.color.ohos_id_color_text_primary'))
          .fontSize($r('sys.float.ohos_id_text_size_button3'))
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .textAlign(TextAlign.Center)
          .maxLines(TEXT_MAX_LINES)
          .minFontScale(MIN_FONT_SCALE)
          .maxFontScale(this.fontSizeScale)

        SymbolGlyph($r('sys.symbol.minus_circle_fill'))
          .fontSize(SYMBOL_SIZE_24VP)
          .fontWeight(SYMBOL_WEIGHT)
          .draggable(false)
          .fontColor([$r('sys.color.ohos_id_color_secondary')])
          .width(ICON_SIZE)
          .transition({ type: TransitionType.All, scale: { x: 0, y: 0, centerX: '50%' } })
          .scale(select.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon } : {})
          .visibility(this.gridComState ? 0 : 1)
          .position({
            x: this.blockWidth - 52, // gridItem-padding: 16,row-padding: 12, icon: 24 - 8 = 16
            y: -MARGIN_EIGHT
          })
          .animation({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER,
          })
          .onClick(() => this.handleDeleteClick(select))
          .accessibilityLevel(YES)
          .accessibilityText(
            this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DELETE, this.getAccessibilityText(select.text))
          )
      }
      .borderRadius(50)
      .padding({
        left: TEXT_PADDING_LEFT_RIGHT,
        right: TEXT_PADDING_LEFT_RIGHT,
      })
      .backgroundColor(
        this.isTouchDown && select.id === this.content.id ? this.touchDown
          : select.id === this.hoverId ? this.hoverBackgroundColor
          : '')
      .width(this.clickRemoveBtn && select.id === this.content.id ?
        this.textItemEditWidth + 8 : this.textItemEditWidth)
      .translate(this.gridComState ? this.clickRemoveBtn && select.id === this.content.id ?
        { x: 0 } : { x: -4 } : { x: 0 })
      .height('100%')
      .animation(!this.firstIn ? {
        duration: ENTER_EXIT_ICON_DURATION,
        curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
      } : { duration: 0 })
    }
    .scale(select.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {})
    .padding({
      left: MARGIN_EIGHT,
      right: MARGIN_EIGHT
    })
    .height(this.textItemEditHeight)
  }

  // 文本模式添加区域item
  @Builder
  TextBlockAddItemBuilder(select: GridObjectSortComponentItem) {
    Stack() {
      Row() {
      }
      .borderRadius(50)
      .height('100%')
      .width(this.addIconShow && select.id === this.content.id ? this.textItemEditWidth : '100%')
      .translate(this.addIconShow && select.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 })
      .animation({
        duration: ENTER_EXIT_ICON_DURATION,
        curve: COMMON_BEZIER
      })
      .backgroundColor($r('sys.color.ohos_id_color_button_normal'))

      Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        SymbolGlyph($r('sys.symbol.plus'))
          .fontSize(this.getAdaptiveSymbolFontSize())
          .draggable(false)
          .fontColor([$r('sys.color.ohos_id_color_text_secondary')])
          .visibility(this.addIconShow && select.id === this.content.id ? Visibility.None : Visibility.Visible)
          .transition({ type: TransitionType.All, scale: { x: 0, y: 0 } })
          .margin({ right: 4 })
          .animation({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER
          })

        Text(select.text)
          .fontSize($r('sys.float.ohos_id_text_size_button3'))
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .textAlign(TextAlign.Start)
          .maxLines(TEXT_MAX_LINES)
          .minFontScale(MIN_FONT_SCALE)
          .maxFontScale(this.fontSizeScale)

        if (this.gridComState && this.addIconShow && select.id === this.content.id) {
          SymbolGlyph($r('sys.symbol.minus_circle_fill'))
            .fontSize(SYMBOL_SIZE_24VP)
            .fontWeight(SYMBOL_WEIGHT)
            .draggable(false)
            .transition({ type: TransitionType.All, scale: { x: 0, y: 0 } })
            .fontColor([$r('sys.color.ohos_id_color_secondary')])
            .width(ICON_SIZE)
            .translate(this.gridComState ? { x: -MARGIN_EIGHT } : {})
            .position({
              x: this.blockWidth - 44,
              y: -MARGIN_EIGHT
            })
        }
      }
      .borderRadius(50)
      .padding({
        left: TEXT_PADDING_LEFT_RIGHT,
        right: TEXT_PADDING_LEFT_RIGHT,
      })
      .backgroundColor(this.isTouchDown && select.id === this.content.id ? this.touchDown
        : select.id === this.hoverId ? this.hoverBackgroundColor : '')
      .width(this.addIconShow && select.id === this.content.id ? this.textItemEditWidth : '100%')
      .translate(this.addIconShow && select.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 })
      .animation({
        duration: ENTER_EXIT_ICON_DURATION,
        curve: COMMON_BEZIER
      })
      .height('100%')
    }
    .scale(select.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {})
    .padding({
      left: MARGIN_EIGHT,
      right: MARGIN_EIGHT
    })
    .height(this.textItemEditHeight)
  }

  onAddTagLongPressEnd(): void {
    this.addAreaLongPressGesture = false;
    animateTo({
      duration: ENTER_EXIT_ICON_DURATION,
      curve: LONG_TOUCH_SCALE
    }, () => {
      this.longScaleOnePointTwo = 1;
    });
  }

  @Builder
  AddTagBuilder() {
    Grid() {
      ForEach(this.unSelected, (item: GridObjectSortComponentItem, index: number) => {
        GridItem() {
          Stack() {
            if (this.imageText) {
              this.ImageTextBuilder(item, ADD);
            } else {
              this.TextBlockAddItemBuilder(item);
            }
          }
          .onHover((isHover: boolean) => {
            if (isHover) {
              this.hoverId = item.id;
            } else {
              this.hoverId = '';
            }
          })
          .margin({
            bottom: this.imageText ? ROW_GAP : MARGIN_EIGHT
          })
          .clickEffect({ level: ClickEffectLevel.LIGHT })
          .onTouch(this.isOpenAccessibility ? undefined : (event: TouchEvent) => {
            this.handleAddItemTouch(event, item);
          })
          .onClick(this.isOpenAccessibility ? () => this.handleAddItemClick(item) : undefined)
          .gesture(
            LongPressGesture({ repeat: true })
              .onAction((event: GestureEvent) => {
                if (!this.gridComState) {
                  animateTo({
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
                } else {
                  animateTo({
                    duration: ENTER_EXIT_ICON_DURATION,
                    curve: LONG_TOUCH_SCALE
                  }, () => {
                    this.longScaleOnePointTwo = 1.05;
                  })
                }
                this.calcGridHeight();
              })
              .onActionEnd(() => {
                this.onAddTagLongPressEnd();
              })
              .onActionCancel(() => {
                this.onAddTagLongPressEnd();
              })
          )
          .id(`add_grid_item_${index}`)
          .onAppear(()=>{
            // 编辑排序区移除下来的元素在第一个 index 为 0
            if (!this.readFlag && index === this.readIndex4AddArea) {
              this.pointToAddArea();
            }
          })
          .accessibilityGroup(true)
          .accessibilityLevel(YES)
          .accessibilityText(
            this.readFlag ?
            this.getStringByResourceToken(
              ACCESSIBILITY_UNSELECTED_ITEM, this.getAccessibilityText(item.text ?? '')
            ) : this.textAnnouncedForAccessibility
          )
          .accessibilityDescription(
            this.readFlag ? this.getAddTagGridItemAccessibilityDesc() : ' '
          )
        }
        .clip(false)
        .translate(this.getAddAreaItemTranslate(index))
        .animation({
          curve: this.clickRemoveBtn ? DRAG_SPRING : index === this.unSelectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING
        })
      }, (item: GridObjectSortComponentItem) => item.id.toString())
    }
    .translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {} )
    .animation({
      duration: ENTER_EXIT_ICON_DURATION,
      curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
    })
    .columnsTemplate(this.customColumns)
    .padding({
      left: ROW_GAP,
      right: ROW_GAP,
    })
    .clip(false)
    .height(this.addGridHeight)
    .accessibilityLevel(NO)
  }

  getAddTagGridItemAccessibilityDesc(): string { // 图文在编辑态不播报描述 纯文字在编辑态不播报双击长按事件
    return this.options?.type === GridObjectSortComponentType.IMAGE_TEXT ?
      this.menuSwitch ? ' ' : this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC) :
      this.menuSwitch ? this.getStringByResourceToken(ACCESSIBILITY_DOUBLE_CLICK) :
      this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_TEXT_ITEM_DESC)
  }

  handleAddItemTouch(event: TouchEvent, item: GridObjectSortComponentItem): void {
    if (this.clickAddBtn || this.clickRemoveBtn) {
      return;
    }
    if (event.type === TouchType.Down) {
      this.content = item;
      this.isTouchDown = true;
    }
    if (event.type === TouchType.Cancel) {
      this.isTouchDown = false;
      return;
    }
    if (event.type === TouchType.Up) {
      this.isTouchDown = false;
      if (this.addAreaLongPressGesture || this.longScaleOnePointTwo === 1.05 || this.imageText) {
        return;
      }
      animateTo({
        duration: ENTER_EXIT_ICON_DURATION,
        curve: COMMON_BEZIER
      }, () => {
        this.addIconShow = true;
      })
      if (this.options.type === GridObjectSortComponentType.TEXT) {
        this.scaleAddIcon = 1;
      }
      this.scaleIcon = 0;
      const index = this.unSelected.findIndex(i => i.id === item.id);
      this.editGridDataLength = this.selected.length + 1;
      const endPosition = this.getEditItemGridPosition(this.selected, index);
      this.content = item;
      this.unSelectedIndex = index;
      this.clickAddBtn = true;
      this.arrayUnSelectIsChange = 1;
      this.calcGridHeight();
      animateTo({ curve: REMOVE_ADD_SPRING, onFinish: () => {
        if (!this.selected.some(val => val.id === item.id)) {
          this.scaleIcon = 1;
          this.scaleAddIcon = 0;
          this.selected.push(item);
          this.unSelected.splice(index, 1);
          this.calcGridHeight();
          this.arrayUnSelectIsChange = 2;
          this.addItemMoveX = 0;
          this.addItemMoveY = 0;
          if (!this.gridComState) {
            this.onSaveEdit();
          }
          animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER }, () => {
            this.addIconShow = false;
          });
          this.clickAddBtn = false;
        }
      } }, () => {
        this.addItemMoveX = endPosition.x;
        this.addItemMoveY = endPosition.y;
      })

      this.readFlag = false;
      this.readIndex4EditArea = this.editGridDataLength - 1;
      this.textAnnouncedForAccessibility = this.getStringByResourceToken(
        ACCESSIBILITY_UNSELECTED_ITEM_ADD,
        this.getAccessibilityText(this.content?.text ?? ''),
        Math.floor(this.readIndex4EditArea / this.colNum) + 1,
        this.readIndex4EditArea % this.colNum + 1
      );
    }
  }

  handleAddItemClick(item: GridObjectSortComponentItem): void {
    if (this.clickAddBtn || this.clickRemoveBtn) {
      return;
    }
    this.content = item;

    this.isTouchDown = false;
    if (this.addAreaLongPressGesture || this.longScaleOnePointTwo === 1.05 || this.imageText) {
      return;
    }
    animateTo({
      duration: ENTER_EXIT_ICON_DURATION,
      curve: COMMON_BEZIER
    }, () => {
      this.addIconShow = true;
    })
    if (this.options.type === GridObjectSortComponentType.TEXT) {
      this.scaleAddIcon = 1;
    }
    this.scaleIcon = 0;
    const index = this.unSelected.findIndex(i => i.id === item.id);
    this.editGridDataLength = this.selected.length + 1;
    const endPosition = this.getEditItemGridPosition(this.selected, index);
    this.content = item;
    this.unSelectedIndex = index;
    this.clickAddBtn = true;
    this.arrayUnSelectIsChange = 1;
    this.calcGridHeight();
    animateTo({
      curve: REMOVE_ADD_SPRING, onFinish: () => {
        if (!this.selected.some(val => val.id === item.id)) {
          this.scaleIcon = 1;
          this.scaleAddIcon = 0;
          this.selected.push(item);
          this.unSelected.splice(index, 1);
          this.calcGridHeight();
          this.arrayUnSelectIsChange = 2;
          this.addItemMoveX = 0;
          this.addItemMoveY = 0;
          if (!this.gridComState) {
            this.onSaveEdit();
          }
          animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER
          }, () => {
            this.addIconShow = false;
          });
          this.clickAddBtn = false;
        }
      }
    }, () => {
      this.addItemMoveX = endPosition.x;
      this.addItemMoveY = endPosition.y;
    })

    this.readFlag = false;
    this.readIndex4EditArea = this.editGridDataLength - 1;
    this.textAnnouncedForAccessibility = this.getStringByResourceToken(
      ACCESSIBILITY_UNSELECTED_ITEM_ADD,
      this.getAccessibilityText(this.content?.text ?? ''),
      Math.floor(this.readIndex4EditArea / this.colNum) + 1,
      this.readIndex4EditArea % this.colNum + 1
    );

  }

  @Builder
  EditTagBuilder() {
    Column() {
      Grid() {
        ForEach(this.selected, (select: GridObjectSortComponentItem, index: number) => {
          GridItem() {
            Stack() {
              if (this.imageText) {
                this.ImageTextBuilder(select, DELETE);
              } else {
                this.TextBlockBuilder(select);
              }
            }
            .onHover((isHover: boolean) => {
              if (isHover) {
                this.hoverId = select.id;
              } else {
                this.hoverId = '';
              }
            })
            .clickEffect({ level: ClickEffectLevel.LIGHT })
            .clip(false)
            .margin({
              bottom: this.imageText ? ROW_GAP : this.gridComState ? ROW_GAP : MARGIN_EIGHT
            })
            .onTouch((event: TouchEvent) => {
              if (this.clickAddBtn || this.clickRemoveBtn) {
                return;
              }
              if (event.type === TouchType.Down) {
                this.content = select;
                this.isTouchDown = true;
              }

              if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                this.isTouchDown = false;
                animateTo({
                  duration: ENTER_EXIT_ICON_DURATION,
                  curve: LONG_TOUCH_SCALE
                }, () => {
                  this.longScaleOnePointTwo = 1;
                })
              }
            })
            .id(`edit_grid_item_${index}`)
            .onVisibleAreaChange([0.0, 1.0], (isVisible: boolean, currentRatio: number) => {
              if (isVisible) {
                if (!this.readFlag && index === this.readIndex4EditArea) {
                  this.pointToNextOne();
                }
              }
            })
            .accessibilityGroup(true)
            .accessibilityLevel(YES)
            .accessibilityText(
              this.readFlag ?
              this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM, this.getAccessibilityText(select.text)) :
              this.textAnnouncedForAccessibility
            )
            .accessibilityDescription(
              this.readFlag ?
              this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DESC) : ''
            )
          }
          .clip(false)
          .translate(this.getShowAreaItemTranslate(index))
          .animation({
            curve: this.isStartDrag ? DRAG_SPRING : index === this.selectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING,
          })
          .visibility(select.visibility)
        }, (item: GridObjectSortComponentItem) => item.id.toString())
      }
      .accessibilityLevel(NO)
      .parallelGesture(
        LongPressGesture({ repeat: true })
          .onAction((event: GestureEvent) => {
            if (!this.gridComState) {
              animateTo({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
              }, () => {
                this.gridComState = true;
              });
              this.menuSwitch = true;
              setTimeout(() => {
                this.pointToRepeat(EDIT);
              }, ENTER_EXIT_ICON_DURATION);
            } else {
              animateTo({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: LONG_TOUCH_SCALE
              }, () => {
                this.longScaleOnePointTwo = 1.05;
              });

              if (event.repeat && !this.vibrationDone) {
                try {
                  vibrator.startVibration({
                    type: 'time',
                    duration: 1000
                  }, {
                    id: 0,
                    usage: 'alarm'
                  }).then(() => {
                    this.vibrationDone = true;
                  })
                } catch {
                  this.vibrationDone = false;
                }
              }
            }
            this.calcGridHeight();
          })
          .onActionCancel(() => {
            if (this.isStartDrag) {
              this.insertItem(this.itemIndex, this.itemIndex);
            }
          })
      )
      .clip(false)
      .editMode(this.gridComState)
      .columnsTemplate(this.customColumns)
      .padding({
        left: ROW_GAP,
        right: ROW_GAP
      })
      .height(this.editGridHeight)
      .animation(!this.firstIn ? {
        duration: ENTER_EXIT_ICON_DURATION,
        curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
      } : { duration: 0 })
      .onItemDragStart((event: ItemDragInfo, itemIndex: number) => {
        this.itemIndex = itemIndex;
        this.selectedIndex = -1;
        if (!this.gridComState) {
          return;
        }
        this.isStartDrag = true;
        this.insertIndex = itemIndex;
        this.dragContent = this.selected[itemIndex];
        this.dragContentIndex = itemIndex;
        this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_START,
          this.getAccessibilityText(this.dragContent?.text ?? ''));
        this.sendAccessibility();
        return this.PixelMapBuilder(this.dragContent?.symbolStyle || this.dragContent?.url, this.dragContent?.text);
      })
      .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
        this.insertItem(itemIndex, insertIndex);
      })
      .onItemDragMove(
        (event: ItemDragInfo, itemIndex: number, insertIndex: number) =>
        this.onDragMoveEvent(event, itemIndex, insertIndex)
      )
      .onItemDragLeave((event: ItemDragInfo, itemIndex: number) => {
        this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_ILLEGAL_AREA);
        this.sendAccessibility();
      })
    }
    .accessibilityLevel((this.selected.length === 0) ? YES : NO)
    .parallelGesture(
      LongPressGesture({ repeat: true })
        .onAction(() => {
          this.menuSwitch = true;
        })
        .onActionEnd(() => {
          let eventInfo: accessibility.EventInfo = ({
            type: 'announceForAccessibility', // 表示主动播报的事件。
            bundleName: this.bundleName, // 目标应用名；不可缺省。
            triggerAction: 'common', // 表示没有特定操作，用于主动聚焦、主动播报等场景。
            textAnnouncedForAccessibility: getContext().resourceManager
              .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE) // 主动播报的内容。
          });
          accessibility.sendAccessibilityEvent(eventInfo);
        }))
    .accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_RESIDENT_AREA))
    .accessibilityDescription(this.menuSwitch ? ' ' :
    this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC))
  }

  pointToRepeat(type: string): void {
    this.readFlag = false;
    let customId: string = '';
    let index = -1;
    if (type === ADD) {
      index = this.unSelected.findIndex(i => i.id === this.content.id);
      this.readIndex4AddArea = index;
      customId = `add_grid_item_${index}`
    } else {
      index = this.selected.findIndex(i => i.id === this.content.id);
      this.readIndex4EditArea = index;
      customId = `edit_grid_item_${index}`
    }

    this.textAnnouncedForAccessibility = getContext().resourceManager
      .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE);

    let eventInfo: accessibility.EventInfo = ({
      type: 'requestFocusForAccessibility',
      bundleName: this.bundleName,
      triggerAction: 'common',
      customId: customId
    });

    accessibility.sendAccessibilityEvent(eventInfo).then(() => {
      setTimeout(()=>{
        this.readFlag = true;
        this.readIndex4EditArea = -1;
        this.readIndex4AddArea = -1;
        this.textAnnouncedForAccessibility = '';
      }, ENTER_EXIT_ICON_DURATION)
    });
  }

  insertItem(itemIndex: number, insertIndex: number): void {
    if (!this.gridComState) {
      return;
    }
    this.vibrationDone = false;
    animateTo({
      duration: ENTER_EXIT_ICON_DURATION,
      curve: LONG_TOUCH_SCALE
    }, () => {
      this.longScaleOnePointTwo = 1;
    })
    this.isStartDrag = false;
    if (insertIndex !== -1) {
      this.selected.splice(itemIndex, 1);
      this.selected.splice(insertIndex, 0, this.dragContent);
      this.textAnnouncedForAccessibility = this.getStringByResourceToken(
        ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP,
        Math.floor(insertIndex / this.colNum) + 1,
        insertIndex % this.colNum + 1);
    } else {
      this.insertIndex = itemIndex;
      this.textAnnouncedForAccessibility = this.getStringByResourceToken(
        ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP,
        Math.floor(itemIndex / this.colNum) + 1,
        itemIndex % this.colNum + 1
      );
    }
    this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
    this.dragContent.visibility = Visibility.Visible;
    this.calcGridHeight();
    this.readFlag = false;
    this.readIndex4EditArea = this.insertIndex;
  }

  pointToNextOne(): void {
    // 等节点渲染好
    let eventInfo: accessibility.EventInfo = ({
      type: 'requestFocusForAccessibility',
      bundleName: this.bundleName,
      triggerAction: 'common',
      customId: `edit_grid_item_${this.readIndex4EditArea}`
    });

    accessibility.sendAccessibilityEvent(eventInfo).then(() => {
      setTimeout(() => {
        this.readFlag = true;
        this.readIndex4EditArea = -1;
        this.readIndex4AddArea = -1;
        this.textAnnouncedForAccessibility = '';
      }, ENTER_EXIT_ICON_DURATION);
    });
  }

  calcAreaInfo(): void {
    // 重新获取字体倍数，并重新计算列数
    this.calcColNum();
    this.blockWidth = this.getBlockWidth(); // gridItem width
    this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
    this.imageItemWidth = this.blockWidth - 16; // image Width
    this.calcTextItemEditHeight();
    this.blockHeight = this.imageText ? this.imageItemWidth + EDIT_BLOCK_TEXT_ITEM_SAFE_MARGIN : this.gridComState ?
      this.textItemEditHeight + EDIT_BLOCK_TEXT_ITEM_SAFE_MARGIN :
      this.textItemEditHeight + DEFAULT_BLOCK_TEXT_ITEM_SAFE_MARGIN;
    this.calcGridHeight();
  }

  build() {
    Column() {
      // header
      this.HeaderTitleBuilder()
      // main
      Scroll() {
        Column() {
          // showArea
          SubHeader({
            primaryTitle: '',
            secondaryTitle: this.options.showAreaTitle || $r('sys.string.ohos_grid_edit_subtitle_sort'),
            icon: '',
            operationType: OperationType.BUTTON
          })
            .margin({ bottom: MARGIN_EIGHT })
          this.EditTagBuilder()
          // addArea
          SubHeader({
            primaryTitle: '',
            secondaryTitle: this.options.addAreaTitle || $r('sys.string.ohos_grid_edit_subtitle_add'),
            icon: '',
            operationType: OperationType.BUTTON
          })
            .translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {})
            .animation({
              duration: ENTER_EXIT_ICON_DURATION,
              curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            })
            .margin({ bottom: MARGIN_EIGHT })
            .onAreaChange((oldValue: Area, newValue: Area) => {
              this.subTitleHeight = Number(newValue.height);
            })
          this.AddTagBuilder()
        }
        .onAreaChange((oldValue: Area, newValue: Area) => {
          this.areaWidth = Number(newValue.width);
          this.calcAreaInfo();
        }).width('100%')
      }
    }
    .width('100%')
    .height('90%')
  }

  getStringByResourceToken(value?: string, ...args: Array<string | number>): string {
    if (value) {
      try {
        return getContext(this).resourceManager.getStringByNameSync(value, ...args);
      } catch (error) {
        hilog.error(0x3900, 'Ace', `GridObjectSortComponent getStringByResourceToken, error: ${error.toString()}`);
      }
    }
    return '';
  }

  /**
   * 获取无障碍文本
   *
   * @param resource 资源
   * @param selected select state
   * @returns string
   */
  getAccessibilityText(resource: ResourceStr): string {
    try {
      let resourceString: string = '';
      if (typeof resource === 'string') {
        resourceString = resource;
      } else {
        if (resource.id === -1 ) {
          resourceString = getContext()?.resourceManager?.getStringByNameSync(resource.params?.[0].split('.').pop());
        } else {
          resourceString = getContext()?.resourceManager?.getStringSync(resource);
        }
      }
      return resourceString;
    } catch (error) {
      let code: number = (error as BusinessError).code;
      let message: string = (error as BusinessError).message;
      hilog.error(0x3900, 'Ace', `GridObjectSortComponent getAccessibilityText error, code: ${code}, message: ${message}`);
      return '';
    }
  }
}