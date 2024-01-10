/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
import { ComposeTitleBar } from "@ohos.arkui.advanced.ComposeTitleBar";
import { EditableTitleBar, EditableLeftIconType } from "@ohos.arkui.advanced.EditableTitleBar";
import { SubHeader } from '@ohos.arkui.advanced.SubHeader';

//  declaring Constants
const COL_IMAGE_TEXT = 3;
const COL_TEXT = 4;
const BLOCK_TEXT_HEIGHT = 36;
const ICON_SIZE = 24;
const IMAGE_DEFAULT = 56;
const TEXT_PADDING_LEFT_RIGHT = 12;
const MARGIN_EIGHT = 8;
const ROW_GAP = 16;
const DURATION = 300;
const ENTER_EXIT_ICON_DURATION = 200;
const COMMON_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1);
const DRAG_SPRING = curves.interpolatingSpring(0, 1, 400, 38);
const REMOVE_ADD_SPRING = curves.interpolatingSpring(0, 1, 150, 24);
const LONG_TOUCH_SCALE = curves.cubicBezierCurve(0.2, 0, 0.2, 1);

// declaring interface, enum, class
export interface GridObjectSortComponentItem {
  id: number | string;
  text: ResourceStr;
  selected: boolean;
  order: number;
  url?: ResourceStr;
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

interface ItemPosition {
  id: number | string;
  globalPositionX: number;
  globalPositionY: number;
}

class MenuItem {
  value: Resource;
  isEnabled: boolean;
  action: () => void;

  constructor(value: Resource, enabled: boolean, action: () => void) {
    this.value = value;
    this.isEnabled = enabled;
    this.action = action;
  }
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
  @State content: GridObjectSortComponentItem = { id: '', text: '', selected: false, order: 0 };
  @State hoverId: number | string = ''
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
  @State editGridDataLength: number = -1;
  @State isTouchDown: boolean = false;
  @State endX: number = 0;
  @State endY: number = 0;
  @State unSelectedIndex: number = 0;
  @State clickAddBtn: boolean = false;
  @State selectedIndex: number = -1;
  @State gridHeight: number = 0;
  @State clickRemoveBtn: boolean = false;
  @State addAreaLongPressGesture: boolean = false;
  @State itemMoveX: number = 0;
  @State itemMoveY: number = 0;
  @State arraySelectIsChange: number = 0;
  @State arrayUnSelectIsChange: number = 0;
  @State textItemEditWidth: number = 0;
  @State imageItemWidth: number = 0;
  @State saveClick: boolean = false;
  // current column, text: 4 column  , image_text: 3 column
  private colNum: number = 3;
  private vibrationDone: boolean = false;
  private touchDown: Resource = $r('sys.color.ohos_id_color_click_effect');
  private touchBorderRadius: Resource = $r('sys.float.ohos_id_corner_radius_clicked');
  private hoverBackgroundColor: Resource = $r('sys.color.ohos_id_color_hover');
  private focusBorder: Resource = $r('sys.color.ohos_id_color_focused_outline');
  private imageText: boolean = false
  private initPosition: ItemPosition[] = []
  scroller: Scroller = new Scroller();
  onSave?: (select: GridObjectSortComponentItem[], unselect: GridObjectSortComponentItem[]) => void;
  onCancel?: () => void;

  // component rendering
  aboutToAppear() {
    this.dataList.length = 50;
    this.selected = this.dataList && this.deduplicate(this.dataList).filter(val => val.selected).sort(this.sortBy());
    this.unSelected = this.dataList && this.deduplicate(this.dataList).filter(val =>!val.selected).sort(this.sortBy());
    this.copySelected = this.selected.slice();
    this.copyUnSelected = this.unSelected.slice();
    this.editGridDataLength = this.selected.length;
    this.imageText = this.options.type === GridObjectSortComponentType.IMAGE_TEXT;
    this.colNum = this.imageText ? COL_IMAGE_TEXT : COL_TEXT;
  }

  deduplicate(arr: GridObjectSortComponentItem[]) {
    const result: GridObjectSortComponentItem[] = [];
    arr.forEach(item => {
      if (!result.some(x => x.id === item.id)) {
        result.push(item);
      }
    })
    return result
  }

  // header
  private menuItems: Array<MenuItem> = [
    new MenuItem($r('sys.media.ohos_ic_public_edit'), true, () => {
      this.goEdit();
    }),
  ]

  onGridComStateChange() {
    this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16
    if (!this.imageText) {
      this.blockHeight = this.gridComState ? 44 : BLOCK_TEXT_HEIGHT
    }
  }

  sortBy() {
    return (a: GridObjectSortComponentItem, b: GridObjectSortComponentItem) => {
      return a.order - b.order;
    }
  }

  // cancel edit function
  cancelEdit() {
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
    this.onCancel && this.onCancel();
  }

  // Enter edit function
  goEdit() {
    animateTo({
      duration: ENTER_EXIT_ICON_DURATION,
      curve: COMMON_BEZIER,
    }, () => {
      this.gridComState = true;
    });
    this.menuSwitch = true;
  }

  // save data
  onSaveEdit() {
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
      this.onSave && this.onSave(selected, unSelected);
    });
    setTimeout(() => {
      this.saveClick = false
    }, ENTER_EXIT_ICON_DURATION)
    this.menuSwitch = false
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
  }

  // get columnsTemplate
  customColumnsTemplate(): string {
    let fr: string = "1fr 1fr 1fr 1fr";
    if (this.imageText) {
      fr = "1fr 1fr 1fr";
    }
    return fr;
  }

  getNewData(data: GridObjectSortComponentItem[], state: boolean, startIndex: number): GridObjectSortComponentItem[] {
    return data.map((val, index) => {
      val.selected = state;
      val.order = startIndex + index;
      return val;
    })
  }

  getBlockWidth(): number {
    const blockWidth = (this.areaWidth - 32) / this.colNum;
    return blockWidth;
  }

  // bottom => top position
  getEditItemGridPosition(data: GridObjectSortComponentItem[], removeIndex: number): PositionXY {
    const len = data.length
    const col: number = this.colNum
    const insertCol = Math.trunc(len % col)
    const removeCol = Math.trunc(removeIndex % col)
    let xNew = Math.abs(insertCol - removeCol) * this.blockWidth

    if (insertCol < removeCol) {
      xNew = -xNew
    } else if (insertCol > removeCol) {
      xNew = xNew
    } else {
      xNew = 0
    }

    let yNew = 0
    let removeRow = Math.trunc(removeIndex / this.colNum)
    const subTitleHeight: number = 56
    yNew = (removeRow + 1) * this.blockHeight + subTitleHeight
    return {
      x: xNew,
      y: yNew
    }
  }

  getAddItemGridPosition(removeIndex: number): PositionXY {
    const len = this.unSelected.length
    const col: number = this.colNum
    const remainder = Math.trunc((len % col))
    const removeCol = Math.trunc(removeIndex % col)
    const insertCol = remainder
    let xNew = Math.abs(insertCol - removeCol) * this.blockWidth
    if (insertCol < removeCol) {
      xNew = -xNew
    } else if (insertCol > removeCol) {
      xNew = xNew
    } else {
      xNew = 0
    }
    let yNew = 0
    let removeRow = Math.trunc(removeIndex / this.colNum)
    const num = len % col === 0 ? 0 : 1
    let unSelectRowTotal = Math.trunc(len / this.colNum) + num
    const len1 = this.selected.length
    const num1 = len1 % col === 0 ? 0 : 1
    let selectRowTotal = Math.trunc(len1 / this.colNum) + num1
    const subTitleHeight: number = 56
    if (remainder === 0) {
      yNew = (unSelectRowTotal + (selectRowTotal - removeRow)) * this.blockHeight + subTitleHeight
    } else {
      yNew = (unSelectRowTotal - 1 + (selectRowTotal - removeRow)) * this.blockHeight + subTitleHeight
    }
    return {
      x: xNew,
      y: yNew
    }
  }

  // Displacement to the first position
  getAddItemGridFirstPosition(removeIndex: number): PositionXY {
    const len = this.selected.length
    const col: number = this.colNum
    const removeCol = (removeIndex + 1) % col
    const currentLine = Math.ceil((removeIndex + 1) / col)
    const totalRows = Math.ceil(len / col)
    const bool = this.imageText
    let xNew = 0
    if (removeCol === 0) {
      xNew = bool ? -this.blockWidth * 2 : -this.blockWidth * 3
    } else {
      xNew = -this.blockWidth * (removeCol - 1)
    }
    const subTitleHeight: number = 56
    let yNew = 0
    const removeNumY = totalRows - currentLine
    yNew = (removeNumY + 1) * (this.blockHeight) + subTitleHeight
    return {
      x: xNew,
      y: yNew
    }
  }

  getCoveringGridPosition(data: GridObjectSortComponentItem[], index: number, currentClickIndex: number): PositionXY {
    const len = data.length;
    let xNew = 0;
    let yNew = 0;
    if (index > currentClickIndex) {
      if (currentClickIndex === len - 1) {
        xNew = 0;
        yNew = 0;
      } else {
        if (this.arraySelectIsChange !== 2) {
          xNew = (index) % this.colNum === 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
          yNew = (index) % this.colNum === 0 ? -this.blockHeight : 0;
        }
      }
    }
    return {
      x: xNew,
      y: yNew
    }
  }

  onDragMoveEvent(event: ItemDragInfo, itemIndex: number, insertIndex: number) {
    if (!this.gridComState || (event.x < this.blockWidth / 3 && event.y < this.blockHeight / 3)) {
      return
    }
    let targetIndex = insertIndex;
    if (targetIndex < 0) {
      targetIndex = this.selected.length - 1;
    }
    this.insertIndex = insertIndex;
  }

  handleDeleteClick(content: GridObjectSortComponentItem) {
    if (this.clickRemoveBtn) return
    this.scaleIcon = 0;
    this.clickRemoveBtn = true;
    this.arraySelectIsChange = 1;
    let currentIndex = 0;
    this.content = content;
    this.selected.forEach((val, i) => {
      if (val.id === content.id) {
        currentIndex = i;
      }
    });
    this.selectedIndex = currentIndex;
    setTimeout(() => {
      this.scaleIcon = 1;
      this.arraySelectIsChange = 2;
      this.unSelected.push(content);
      this.selected.splice(currentIndex, 1);
      this.editGridDataLength = this.editGridDataLength - 1;
      this.clickRemoveBtn = false;
    }, 500)
  }

  getCoodXY(index: number): PositionXY {
    const gridCol = this.colNum;
    let x = 0;
    let y = 0;
    if (index >= this.insertIndex) {
      // item  newline
      if (Math.trunc(index % gridCol) === gridCol - 1) {
        x = x - this.blockWidth * (gridCol - 1)
        y = y + this.blockHeight
      } else {
        // right move
        x = x + this.blockWidth
      }
    }
    if (!this.isStartDrag) {
      x = 0;
      y = 0;
    }
    return { x, y }
  }

  getGridNum(data: GridObjectSortComponentItem[], state?: string): number {
    let len = data.length;
    let num = 0;
    if (state) {
      if (this.isStartDrag || Math.trunc(len % this.colNum) !== 0 && this.editGridDataLength === len || this.clickAddBtn) {
        num = 1
      }
    } else {
      if (Math.trunc(len % this.colNum) !== 0) {
        num = 1
      }
    }
    return num
  }

  // calculated altitude
  getGridHeight(data: GridObjectSortComponentItem[], state?: string): number {
    let height = 0
    let selectLen = data.length
    let dataArray = data
    const rowNumber = Math.trunc(selectLen / this.colNum) + this.getGridNum(dataArray, state)
    height = this.blockHeight * rowNumber
    if (selectLen === 0) {
      height = 0
    }
    if (state) {
      this.gridHeight = height
    }
    return height
  }

  // top item position
  getXY(data: GridObjectSortComponentItem[], index: number, currentClickIndex: number): PositionXY {
    let xNew = 0
    let yNew = 0
    if (!this.isStartDrag) {
      if (this.clickRemoveBtn) {
        if (index === currentClickIndex) {
          xNew = this.getAddItemGridPosition(currentClickIndex).x
          yNew = this.getAddItemGridPosition(currentClickIndex).y
        } else {
          xNew = this.getCoveringGridPosition(data, index, currentClickIndex).x
          yNew = this.getCoveringGridPosition(data, index, currentClickIndex).y
        }
      }
    } else {
      xNew = this.getCoodXY(index).x
      yNew = this.getCoodXY(index).y
    }
    return {
      x: xNew,
      y: yNew
    }
  }

  getCoveringGridPositionBottom(data: GridObjectSortComponentItem[], index: number, currentClickIndex: number): PositionXY {
    const len = data.length
    let xNew = 0
    let yNew = 0
    if (index > currentClickIndex) {
      if (currentClickIndex === len - 1) {
        xNew = 0
        yNew = 0
      } else {
        if (this.arrayUnSelectIsChange !== 2) {
          xNew = (index) % this.colNum === 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth
          yNew = (index) % this.colNum === 0 ? -this.blockHeight : 0
        }
      }
    }
    return {
      x: xNew,
      y: yNew
    }
  }
  // bottom item position
  getUnSelectXY(data: GridObjectSortComponentItem[], index: number, currentClickIndex: number): PositionXY {
    let xNew = 0
    let yNew = 0
    if (this.clickAddBtn) {
      if (index === this.unSelectedIndex) {
        xNew = this.endX
        yNew = -this.endY
      } else {
        xNew = this.getCoveringGridPositionBottom(data, index, currentClickIndex).x
        yNew = this.getCoveringGridPositionBottom(data, index, currentClickIndex).y
      }
    }
    return {
      x: xNew,
      y: yNew
    }
  }

  @Builder
  PixelMapBuilder() {
    Stack({ alignContent: Alignment.Center }) {
      if (this.imageText) {
        Column() {
          Image(this.content.url)
            .draggable(false)
            .height(this.options.imageSize || IMAGE_DEFAULT)
            .width((this.options.imageSize || IMAGE_DEFAULT))
          Text(this.content.text)
            .textAlign(TextAlign.Center)
            .fontSize($r('sys.float.ohos_id_text_size_button3'))
            .margin({ top: 2 })
            .maxLines(1)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .textAlign(TextAlign.Center)

          Image($r("sys.media.ohos_ic_public_remove_filled"))
            .draggable(false)
            .fillColor($r("sys.color.ohos_id_color_secondary"))
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
          Text(this.content.text)
            .fontColor($r('sys.color.ohos_id_color_text_primary'))
            .fontSize($r('sys.float.ohos_id_text_size_button3'))
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .textAlign(TextAlign.Center)
            .maxLines(1)
          Image($r("sys.media.ohos_ic_public_remove_filled"))
            .draggable(false)
            .fillColor($r("sys.color.ohos_id_color_secondary"))
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
        .height(28)
      }
    }
    .clip(false)
    .height(this.blockHeight * 1.5)
    .width(this.blockWidth * 1.2)
  }

  @Builder
  MoveMask() {
    Stack({ alignContent: Alignment.Center }) {
      if (this.imageText) {
        Column() {
          Image(this.content.url)
            .draggable(false)
            .height(this.options.imageSize || IMAGE_DEFAULT)
            .width((this.options.imageSize || IMAGE_DEFAULT))
          Text(this.content.text)
            .textAlign(TextAlign.Center)
            .fontSize($r('sys.float.ohos_id_text_size_button3'))
            .margin({ top: 2 })
            .maxLines(1)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .textAlign(TextAlign.Center)

          Image($r("sys.media.ohos_ic_public_remove_filled"))
            .draggable(false)
            .fillColor($r("sys.color.ohos_id_color_secondary"))
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
      } else {
        Row() {
          Text(this.content.text)
            .fontColor($r('sys.color.ohos_id_color_text_primary'))
            .fontSize($r('sys.float.ohos_id_text_size_button3'))
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .textAlign(TextAlign.Center)
            .maxLines(1)
          Image($r("sys.media.ohos_ic_public_remove_filled"))
            .draggable(false)
            .fillColor($r("sys.color.ohos_id_color_secondary"))
            .width(ICON_SIZE)
            .height(ICON_SIZE)
            .position({
              x: this.blockWidth - 52, // gridItem-padding: 16, row-padding: 12, icon: 24 - 8 = 16
              y: -MARGIN_EIGHT
            })
        }
        .borderRadius(50)
        .padding({
          left: TEXT_PADDING_LEFT_RIGHT,
          right: TEXT_PADDING_LEFT_RIGHT,
        })
        .alignItems(VerticalAlign.Center)
        .justifyContent(FlexAlign.Center)
        .backgroundColor($r('sys.color.ohos_id_color_button_normal'))
        .width(this.textItemEditWidth)
        .height(28)
      }
    }
    .height(this.blockHeight)
    .width(this.blockWidth)
  }

  @Builder
  HeaderTitleBuilder() {
    ComposeTitleBar({
      title: this.options.normalTitle || $r('sys.string.ohos_grid_edit_title_chanel'),
      menuItems: this.menuItems,
    })
      .visibility(!this.menuSwitch ? Visibility.Visible : Visibility.None)
    EditableTitleBar({
      leftIconStyle: EditableLeftIconType.Cancel,
      menuItems: [],
      title: this.options.editTitle || $r('sys.string.ohos_grid_edit_title_edit'),
      onCancel: () => {
        this.cancelEdit()
      },
      onSave: () => {
        this.saveClick = true
        this.onSaveEdit()
      }
    })
      .visibility(this.menuSwitch ? Visibility.Visible : Visibility.None)
  }

  @Builder
  ImageTextBuilder(select: GridObjectSortComponentItem, type: string) {
    Column() {
      Column() {
        Image(select.url)
          .draggable(false)
          .height(this.options.imageSize || IMAGE_DEFAULT)
          .width((this.options.imageSize || IMAGE_DEFAULT))
        Text(select.text)
          .textAlign(TextAlign.Center)
          .fontSize($r('sys.float.ohos_id_text_size_button3'))
          .margin({ top: 2 })
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .textAlign(TextAlign.Center)

        Image($r("sys.media.ohos_ic_public_add_norm_filled"))
          .draggable(false)
          .visibility(type === "add" ? Visibility.Visible : Visibility.Hidden)
          .fillColor($r("sys.color.ohos_id_color_secondary"))
          .width(ICON_SIZE)
          .height(ICON_SIZE)
          .animation({
            duration: DURATION,
            curve: Curve.Linear,
            iterations: 1,
            playMode: PlayMode.Normal,
          })
          .position({
            x: this.blockWidth - 40,
            y: -MARGIN_EIGHT
          })
          .onClick(() => {
            if (this.clickAddBtn) return
            this.scaleIcon = 0
            this.content = select
            const index = this.unSelected.findIndex(i => i.id === select.id)
            this.editGridDataLength = this.selected.length + 1
            const endPosition = this.getEditItemGridPosition(this.selected, index)
            this.unSelectedIndex = index
            this.endX = endPosition.x
            this.endY = endPosition.y
            this.arrayUnSelectIsChange = 1
            this.clickAddBtn = true
            setTimeout(() => {
              this.arrayUnSelectIsChange = 2
              this.scaleIcon = 1
              this.selected.push(select);
              this.unSelected.splice(index, 1)
              this.endX = 0
              this.endY = 0
              if (!this.gridComState) {
                this.onSaveEdit()
              }
              this.clickAddBtn = false
            }, 500)
          })

        Image($r("sys.media.ohos_ic_public_remove_filled"))
          .draggable(false)
          .fillColor($r("sys.color.ohos_id_color_secondary"))
          .visibility(type === "delete" && this.gridComState ? Visibility.Visible : Visibility.Hidden)
          .width(ICON_SIZE)
          .height(ICON_SIZE)
          .transition({ type: TransitionType.All, scale: { x: 0, y: 0 } })
          .position({
            x: this.blockWidth - 40,
            y: -MARGIN_EIGHT
          })
          .animation({
            duration: DURATION,
            curve: Curve.Linear,
          })
          .onClick(() => this.handleDeleteClick(select))
      }
      .alignItems(HorizontalAlign.Center)
      .justifyContent(FlexAlign.Center)
      .width('100%')
      .height(this.imageItemWidth)
      .padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT })
      .borderRadius((this.isTouchDown && select.id === this.content.id) || select.id === this.hoverId ? this.touchBorderRadius : 0)
      .backgroundColor(
          this.isTouchDown && select.id === this.content.id
          ? this.touchDown : select.id === this.hoverId ? this.hoverBackgroundColor : ''
      )
      .scale(select.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {})
    }
    .padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT })
    .width('100%')
  }


  // 文本模式拖动排序区域item
  @Builder
  TextBlockBuilder(select: GridObjectSortComponentItem) {
    Stack() {
      Row() {

      }
      .borderRadius(50)
      .width(this.clickRemoveBtn && select.id === this.content.id ? this.textItemEditWidth + 8 : this.textItemEditWidth)
      .translate(this.gridComState ? this.clickRemoveBtn && select.id === this.content.id ? { x: 0 } : { x: -4 } : {
                                                                                                                     x: 0
                                                                                                                   })
      .height('100%')
      .animation({
        duration: ENTER_EXIT_ICON_DURATION,
        curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
      })
      .backgroundColor($r('sys.color.ohos_id_color_button_normal'))

      Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        Image($r("sys.media.ohos_ic_public_add"))
          .width(12)
          .height(12)
          .draggable(false)
          .fillColor($r('sys.color.ohos_id_color_text_secondary'))
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
          .maxLines(1)
        Image($r("sys.media.ohos_ic_public_remove_filled"))
          .draggable(false)
          .fillColor($r("sys.color.ohos_id_color_secondary"))
          .width(ICON_SIZE)
          .transition({ type: TransitionType.All, scale: { x: 0, y: 0, } })
          .scale(select.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon, centerX: '0' } : {
                                                                                                            centerX: '0'
                                                                                                          })
          .visibility(this.gridComState ? 0 : 1)
          .position({
            x: this.blockWidth - 44, // gridItem-padding: 16,row-padding: 12, icon: 24 - 8 = 16
            y: -MARGIN_EIGHT
          })
          .translate(this.gridComState ? this.clickRemoveBtn && select.id === this.content.id ? { x: 8 } : {
                                                                                                             x: -MARGIN_EIGHT
                                                                                                           } : { x: 0 })
          .animation({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER,
          })
          .onClick(() => this.handleDeleteClick(select))
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
      .width(this.clickRemoveBtn && select.id === this.content.id ? this.textItemEditWidth + 8 : this.textItemEditWidth)
      .translate(this.gridComState ? this.clickRemoveBtn && select.id === this.content.id ? { x: 0 } : { x: -4 } : {
                                                                                                                     x: 0
                                                                                                                   })
      .height('100%')
      .animation({
        duration: ENTER_EXIT_ICON_DURATION,
        curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
      })
    }
    .scale(select.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {})
    .padding({
      left: MARGIN_EIGHT,
      right: MARGIN_EIGHT
    })
    .height(28)
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
        Image($r("sys.media.ohos_ic_public_add"))
          .draggable(false)
          .fillColor($r('sys.color.ohos_id_color_text_secondary'))
          .width(12)
          .height(12)
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
          .textAlign(TextAlign.Center)
          .maxLines(1)

        if (this.gridComState && this.addIconShow && select.id === this.content.id) {
          Image($r("sys.media.ohos_ic_public_remove_filled"))
            .draggable(false)
            .transition({ type: TransitionType.All, scale: { x: 0, y: 0 } })
            .fillColor($r("sys.color.ohos_id_color_secondary"))
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
    .height(28)
  }

  @Builder
  AddTagBuilder() {
    Grid() {
      ForEach(this.unSelected, (item: GridObjectSortComponentItem, index: number) => {
        GridItem() {
          Stack() {
            if (this.imageText) {
              this.ImageTextBuilder(item, "add")
            } else {
              this.TextBlockAddItemBuilder(item)
            }
          }
          .onHover((isHover: boolean) => {
            if (isHover) {
              this.hoverId = item.id
            } else {
              this.hoverId = ''
            }
          })
          .margin({
            bottom: this.imageText ? ROW_GAP : this.gridComState ? ROW_GAP : MARGIN_EIGHT
          })
          .clickEffect({ level: ClickEffectLevel.LIGHT })
          .onTouch((event: TouchEvent) => {
            if (this.clickAddBtn) return
            if(event.type === TouchType.Down)
            {
              this.content = item
              this.isTouchDown = true
            }
            if (event.type === TouchType.Up) {
              this.isTouchDown = false
              if (this.addAreaLongPressGesture || this.longScaleOnePointTwo === 1.05 || this.imageText) return
              animateTo({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
              }, () => {
                this.addIconShow = true
              })
              if (this.options.type === GridObjectSortComponentType.TEXT) {
                this.scaleAddIcon = 1
              }
              this.scaleIcon = 0
              const index = this.unSelected.findIndex(i => i.id === item.id)
              this.editGridDataLength = this.selected.length + 1
              const endPosition = this.getEditItemGridPosition(this.selected, index)
              this.content = item
              this.unSelectedIndex = index
              this.endX = endPosition.x
              this.endY = endPosition.y
              this.clickAddBtn = true
              this.arrayUnSelectIsChange = 1
              setTimeout(() => {
                this.scaleIcon = 1
                this.scaleAddIcon = 0
                this.selected.push(item);
                this.unSelected.splice(index, 1)
                this.arrayUnSelectIsChange = 2
                this.endX = 0
                this.endY = 0
                if (!this.gridComState) {
                  this.onSaveEdit()
                }
                animateTo({
                  duration: ENTER_EXIT_ICON_DURATION,
                  curve: COMMON_BEZIER }, () => {
                  this.addIconShow = false
                })
                this.clickAddBtn = false
              }, 500)
            }
          })
          .gesture(
            LongPressGesture({ repeat: true })
              .onAction((event: GestureEvent) => {
                if (!this.gridComState) {
                  animateTo({
                    duration: ENTER_EXIT_ICON_DURATION,
                    curve: COMMON_BEZIER,
                  }, () => {
                    this.addAreaLongPressGesture = true
                    this.gridComState = true
                  })
                  this.menuSwitch = true
                } else {
                  animateTo({
                    duration: ENTER_EXIT_ICON_DURATION,
                    curve: LONG_TOUCH_SCALE
                  }, () => {
                    this.longScaleOnePointTwo = 1.05
                  })
                }
              })
              .onActionEnd(() => {
                this.addAreaLongPressGesture = false
                animateTo({
                  duration: ENTER_EXIT_ICON_DURATION,
                  curve: LONG_TOUCH_SCALE
                }, () => {
                  this.longScaleOnePointTwo = 1
                })
              })
          )
        }
        .clip(false)
        .translate({
          x: this.getUnSelectXY(this.unSelected, index, this.unSelectedIndex).x,
          y: this.getUnSelectXY(this.unSelected, index, this.unSelectedIndex).y,
        })
        .animation({
          curve: REMOVE_ADD_SPRING,
          onFinish: () => {
            if (item.id === this.content.id && this.clickAddBtn) {
              console.log('animationOnFinish', index, JSON.stringify(item))
            }
          }
        })
      }, (item: GridObjectSortComponentItem) => item.id.toString())
    }
    .columnsTemplate(this.customColumnsTemplate())
    .padding({
      left: ROW_GAP,
      right: ROW_GAP,
    })
    .clip(false)
    .height(this.getGridHeight(this.unSelected) + 120)
    .animation({
      duration: 100,
      curve: Curve.Ease,
    })
  }

  @Builder
  EditTagBuilder() {
    Column() {
      Grid() {
        ForEach(this.selected, (select: GridObjectSortComponentItem, index: number) => {
          GridItem() {
            Stack() {
              if (this.imageText) {
                this.ImageTextBuilder(select, 'delete')
              } else {
                this.TextBlockBuilder(select)
              }
            }
            .onHover((isHover: boolean) => {
              if (isHover) {
                this.hoverId = select.id
              } else {
                this.hoverId = ''
              }
            })
            .clickEffect({ level: ClickEffectLevel.LIGHT })
            .clip(false)
            .margin({
              bottom: this.imageText ? ROW_GAP : this.gridComState ? ROW_GAP : MARGIN_EIGHT
            })
            .onTouch((event: TouchEvent) => {
              if (event.type === TouchType.Down) {
                this.content = select
                this.isTouchDown = true
              }

              if (event.type === TouchType.Up) {
                this.isTouchDown = false
                animateTo({
                  duration: ENTER_EXIT_ICON_DURATION,
                  curve: LONG_TOUCH_SCALE
                }, () => {
                  this.longScaleOnePointTwo = 1
                })
              }
            })
          }
          .clip(false)
          .translate({
            x: this.getXY(this.selected, index, this.selectedIndex).x,
            y: this.getXY(this.selected, index, this.selectedIndex).y,
          })
          .animation({
            curve: this.isStartDrag ? DRAG_SPRING : REMOVE_ADD_SPRING,
          })
          .onAreaChange((oldValue: Area, newValue: Area) => {
            if (!this.isStartDrag) {
              const bool = this.initPosition.some(item => item.id === select.id)
              if (bool) {
                const index = this.initPosition.findIndex(item => item.id === select.id)
                this.initPosition[index] = {
                  id: select.id,
                  globalPositionX: newValue.position.x as number,
                  globalPositionY: newValue.position.y as number
                }
              } else {
                this.initPosition.push({
                  id: select.id,
                  globalPositionX: newValue.position.x as number,
                  globalPositionY: newValue.position.y as number
                })
              }
            }
          })
        }, (item: GridObjectSortComponentItem) => item.id.toString())
      }
      .parallelGesture(
        LongPressGesture({ repeat: true })
          .onAction((event: GestureEvent) => {
            if (!this.gridComState) {
              animateTo({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
              }, () => {
                this.gridComState = true
              })
              this.menuSwitch = true
            } else {
              animateTo({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: LONG_TOUCH_SCALE
              }, () => {
                this.longScaleOnePointTwo = 1.05
              })

              if (event.repeat && !this.vibrationDone) {
                try {
                  vibrator.startVibration({
                    type: 'time',
                    duration: 1000
                  }, {
                    id: 0,
                    usage: 'alarm'
                  }).then(() => {
                    this.vibrationDone = true
                  })
                } catch {
                  this.vibrationDone = false
                }
              }
            }
          })
      )
      .clip(false)
      .editMode(this.gridComState)
      .columnsTemplate(this.customColumnsTemplate())
      .padding({
        left: ROW_GAP,
        right: ROW_GAP
      })
      .height(this.getGridHeight(this.selected, 'edit'))
      .animation({
        duration: 100,
        curve: Curve.Ease,
      })
      .onItemDragStart((event: ItemDragInfo, itemIndex: number) => {
        this.selectedIndex = -1
        if (!this.gridComState) {
          return
        }
        this.isStartDrag = true
        this.selected.splice(itemIndex, 1)
        this.editGridDataLength = this.selected.length + 1
        return this.PixelMapBuilder()
      })
      .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
        if (!this.gridComState) {
          return
        }
        this.vibrationDone = false
        animateTo({
          duration: ENTER_EXIT_ICON_DURATION,
          curve: LONG_TOUCH_SCALE
        }, () => {
          this.longScaleOnePointTwo = 1
        })
        this.isStartDrag = false
        this.selected.splice(insertIndex === -1 ? itemIndex : insertIndex, 0, this.content)
      })
      .onItemDragMove((event: ItemDragInfo, itemIndex: number, insertIndex: number) => this.onDragMoveEvent(event, itemIndex, insertIndex))
    }
  }

  build() {
    Column() {
      // header
      this.HeaderTitleBuilder()
      // main
      Scroll() {
        Column() {
          // showArea
          SubHeader({ secondaryTitle: this.options.showAreaTitle || $r('sys.string.ohos_grid_edit_subtitle_sort') })
            .margin({ bottom: MARGIN_EIGHT })
          this.EditTagBuilder()
          // addArea
          SubHeader({ secondaryTitle: this.options.addAreaTitle || $r('sys.string.ohos_grid_edit_subtitle_add') })
            .margin({ bottom: MARGIN_EIGHT })
          this.AddTagBuilder()
        }
        .onAreaChange((oldValue: Area, newValue: Area) => {
          this.areaWidth = Number(newValue.width);
          this.blockWidth = this.getBlockWidth() // gridItem width
          this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16
          this.imageItemWidth = this.blockWidth - 16 // image Width
          this.blockHeight = this.imageText ? this.imageItemWidth + 16 : this.gridComState ? 44 : BLOCK_TEXT_HEIGHT
        }).width("100%")
      }
    }
    .width('100%')
    .height('90%')
  }
}
