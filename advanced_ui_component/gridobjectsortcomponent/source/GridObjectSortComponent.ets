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
const BLOCK_TEXT_HEIGHT = 46;
const BLOCK_IMAGE_TEXT_HEIGHT = 124;
const COLUMNS_GAP_TEXT = 8;
const ROW_GAP = 16;
const DURATION = 300;
const ICON_SIZE = 24;
const IMAGE_DEFAULT = 56;
const TEXT_PADDING_LEFT_RIGHT = 12;
const COMMON_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1);


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

// common text structure
@Extend(Text) function blockTextStyle(width: number = 65) {
  .fontColor($r('sys.color.ohos_id_color_text_primary'))
  .backgroundColor($r('sys.color.ohos_id_color_button_normal'))
  .fontSize($r('sys.float.ohos_id_text_size_button3'))
  .maxLines(1)
  .textOverflow({ overflow: TextOverflow.Ellipsis })
  .height(28)
  .width(width)
  .textAlign(TextAlign.Center)
  .borderRadius(50)
  .padding({
    left: TEXT_PADDING_LEFT_RIGHT,
    right: TEXT_PADDING_LEFT_RIGHT,
  })
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
  // component state : edit === true   unedited === false
  @State gridComState: boolean = false;
  // component width
  @State areaWidth: number = 0;
  // component item width
  @State blockWidth: number = 0;
  // component item height
  @State blockHeight: number = this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? BLOCK_IMAGE_TEXT_HEIGHT : BLOCK_TEXT_HEIGHT;
  // controlled zoom animation
  @State longScaleOnePointTwo: number = 1;
  @State scaleGridItemNinetyPercent: number = 1;
  @State scaleAddItemNinetyPercent: number = 1;
  @State scaleIcon: number = 1;
  @State addIconShow: boolean = false;
  @State scaleAddIcon: number = 0;
  // whether to start dragging
  @State isStartDrag: boolean = false;
  @State dragNextID: number | string = 0;
  @State insertIndex: number = -1;
  @State editGridDataLength: number = -1;
  @State isTouchDown: boolean = false;
  @State endX: number = 0;
  @State endY: number = 0;
  @State unSelectedIndex: number = 0;
  @State selectedIndex: number = -1;
  @State gridHeight: number = 0;
  @State clickRemoveBtn: boolean = false;
  @State clickAddBtn: boolean = false;
  // current column, text: 4 column  , image_text: 3 column
  private colNum: number = this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? COL_IMAGE_TEXT : COL_TEXT;
  private arraySelectIsChange: number = 0;
  private arrayUnSelectIsChange: number = 0;
  private vibrationDone: boolean = false;
  private touchDown: Resource = $r('sys.color.ohos_id_color_click_effect');
  private touchDownBg: Resource = $r('sys.color.ohos_id_color_hover');
  scroller: Scroller = new Scroller();
  onSave?: (select: GridObjectSortComponentItem[], unselect: GridObjectSortComponentItem[]) => void;
  onCancel?: () => void;

  sortBy() {
    return (a: GridObjectSortComponentItem, b: GridObjectSortComponentItem) => {
      return a.order - b.order;
    }
  }

  // component rendering
  aboutToAppear() {
    this.dataList.length = 50;
    this.selected = this.dataList && this.dataList.filter(val => val.selected).sort(this.sortBy());
    this.unSelected = this.dataList && this.dataList.filter(val =>!val.selected).sort(this.sortBy());
    this.copySelected = this.selected.slice();
    this.copyUnSelected = this.unSelected.slice();
    this.editGridDataLength = this.selected.length;
  }

  // header
  private menuItems: Array<MenuItem> = [
    new MenuItem($r('sys.media.ohos_ic_public_edit'), true, () => {
      this.goEdit();
    }),
  ]

  // cancel edit function
  cancelEdit() {
    this.longScaleOnePointTwo = 1;
    this.scaleGridItemNinetyPercent = 1;
    animateTo({ duration: DURATION }, () => {
      this.gridComState = false;
    });
    this.selected = this.copySelected.slice();
    this.unSelected = this.copyUnSelected.slice();
    this.editGridDataLength = this.selected.length;
    this.onCancel && this.onCancel();
  }

  // Enter edit function
  goEdit() {
    this.scaleGridItemNinetyPercent = 0.9;
    animateTo({ duration: DURATION }, () => {
      this.gridComState = true;
    })
  }

  // save data
  onSaveEdit() {
    this.longScaleOnePointTwo = 1;
    this.scaleGridItemNinetyPercent = 1;
    this.editGridDataLength = this.selected.length;
    animateTo({ duration: DURATION }, () => {
      this.gridComState = false;
    })
    this.copySelected = this.selected.slice();
    this.copyUnSelected = this.unSelected.slice();
    const selected = this.getNewData(this.selected, true, 0);
    const unSelected = this.getNewData(this.unSelected, false, this.selected.length);
    this.selected = selected;
    this.unSelected = unSelected;
    this.onSave && this.onSave(selected, unSelected);
  }

  // component disappear
  aboutToDisappear() {
    animateTo({ duration: DURATION }, () => {
      this.gridComState = false;
    })
    this.selected = this.copySelected;
    this.unSelected = this.copyUnSelected;
  }

  // get columnsTemplate
  customColumnsTemplate(): string {
    let fr: string = "1fr 1fr 1fr 1fr";
    if (this.options.type === GridObjectSortComponentType.IMAGE_TEXT) {
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
    const domWidth = (this.areaWidth - 36) - ROW_GAP * (COL_TEXT - 1);
    const blockWidth = domWidth / COL_TEXT;
    return blockWidth;
  }

  getImageBlockWidth(): number {
    const domWidth = (this.areaWidth - 36) - ROW_GAP * (COL_IMAGE_TEXT - 1);
    const blockWidth = domWidth / COL_IMAGE_TEXT;
    return Math.trunc(blockWidth);
  }

  // bottom => top position
  getEditItemGridPosition(data: GridObjectSortComponentItem[], removeIndex: number): PositionXY {
    const len = data.length
    const col: number = this.colNum
    const remainder = Math.trunc(len % col)
    const removeCol = Math.trunc(removeIndex % col)
    const insertCol = remainder
    let xNew = Math.abs(insertCol - removeCol) * (this.blockWidth + 14)
    if (insertCol < removeCol) {
      xNew = -xNew
    } else if (insertCol > removeCol) {
      xNew = xNew
    } else {
      xNew = 0
    }
    let yNew = 0
    let removeRow = Math.trunc(removeIndex / this.colNum)
    const subTitleHeight: number = 57
    yNew = (removeRow + 1) * (this.blockHeight) + subTitleHeight
    return {
      x: xNew,
      y: yNew
    }
  }

  getAddItemGridPosition(data: GridObjectSortComponentItem[], removeIndex: number): PositionXY {
    const len = data.length
    const col: number = this.colNum
    const remainder = Math.trunc((len % col))
    const removeCol = Math.trunc(removeIndex % col)
    const insertCol = remainder
    let xNew = Math.abs(insertCol - removeCol) * (this.blockWidth + 14)
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

    const subTitleHeight: number = 48
    if (remainder === 0) {
      yNew = (unSelectRowTotal + (selectRowTotal - removeRow)) * (this.blockHeight) + subTitleHeight
    } else {
      yNew = (unSelectRowTotal - 1 + (selectRowTotal - removeRow)) * (this.blockHeight) + subTitleHeight
    }
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
          xNew = (index) % this.colNum === 0 ? (this.blockWidth + 16) * (this.colNum - 1) : -this.blockWidth - 14;
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
    this.dragNextID = this.selected[insertIndex]?.id;
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
      ;
    })
    this.selectedIndex = currentIndex;
    setTimeout(() => {
      this.scaleIcon = 1;
      this.arraySelectIsChange = 2;
      this.unSelected.push(content);
      this.selected.splice(currentIndex, 1);
      this.editGridDataLength = this.editGridDataLength - 1;
      this.clickRemoveBtn = false;
    }, DURATION)
  }

  getCoodXY(index: number): PositionXY {
    const gridCol = this.colNum;
    let x = 0;
    let y = 0;
    if (index >= this.insertIndex) {
      // item  newline
      if (Math.trunc(index % gridCol) === gridCol - 1) {
        x = x - (this.blockWidth * (gridCol - 1)) - (this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? (8 * (gridCol - 1)) - 8 : -((8 * (gridCol - 1)) - 16))
        y = y + this.blockHeight
      } else {
        // right move
        x = x + this.blockWidth + COLUMNS_GAP_TEXT * (gridCol - 1) - (this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? 4 : 8);
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
    height = this.blockHeight * rowNumber + 8
    if (selectLen === 0) {
      height = 0
    }
    if (state) {
      this.gridHeight = height
    }
    return height
  }

  getXY(data: GridObjectSortComponentItem[], index: number, currentClickIndex: number): PositionXY {
    let xNew = 0
    let yNew = 0
    if (!this.isStartDrag) {
      if (this.clickRemoveBtn) {
        if (index === currentClickIndex) {
          xNew = this.getAddItemGridPosition(this.unSelected, currentClickIndex).x;
          yNew = this.getAddItemGridPosition(this.unSelected, currentClickIndex).y;
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
            xNew = (index) % this.colNum === 0 ? (this.blockWidth + 16) * (this.colNum - 1) : -this.blockWidth - 14
            yNew = (index) % this.colNum === 0 ?  -this.blockHeight : 0
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
    Stack() {
      if (this.options.type === GridObjectSortComponentType.IMAGE_TEXT) {
        Stack() {
          this.ImageTextBuilder(this.content, "delete", 'pixe')
        }
        .width(this.blockWidth * this.longScaleOnePointTwo + 2)
        .height(this.blockWidth * this.longScaleOnePointTwo + 2)
        .clip(false)
      } else {
        Stack() {
          Text(this.content.text)
            .blockTextStyle(this.blockWidth)
            .fontSize(14)
            .width(this.blockWidth)
            .height(28)
          Image($r("sys.media.ohos_ic_public_remove_filled"))
            .fillColor($r("sys.color.ohos_id_color_secondary"))
            .width(24)
            .height(24)
            .position({
              x: this.blockWidth * this.longScaleOnePointTwo - 32,
              y: -6
            })
        }
        .clip(false)
        .height(28 * this.longScaleOnePointTwo)
      }
    }
    .padding({
      top: this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? TEXT_PADDING_LEFT_RIGHT : 6,
      right: 6
    })
    .clip(false)
  }

  @Builder
  HeaderTitleBuilder() {
    Stack() {
      if (!this.gridComState) {
        ComposeTitleBar({
          title: this.options.normalTitle || $r('sys.string.ohos_grid_edit_title_chanel'),
          menuItems: this.menuItems,
        })
      } else {
        EditableTitleBar({
          leftIconStyle: EditableLeftIconType.Cancel,
          title: this.options.editTitle || $r('sys.string.ohos_grid_edit_title_edit'),
          onCancel: () => {
            this.cancelEdit()
          },
          onSave: () => {
            this.onSaveEdit()
          }
        })
      }
    }
  }

  @Builder
  ImageTextBuilder(content: GridObjectSortComponentItem, type: string, state?: string) {
    Flex(
      { direction: FlexDirection.Column,
        justifyContent: FlexAlign.Center,
        alignItems: ItemAlign.Center }
    ) {
      if (state || content.id === this.content.id) {
        Image(content.url)
          .draggable(false)
          .height(IMAGE_DEFAULT)
          .width(IMAGE_DEFAULT)
        Text(content.text)
          .fontSize($r('sys.float.ohos_id_text_size_button3'))
          .textAlign(TextAlign.Center)
          .width(this.blockWidth * this.longScaleOnePointTwo)
          .padding({ top: 2, left: TEXT_PADDING_LEFT_RIGHT, right: TEXT_PADDING_LEFT_RIGHT })
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .textAlign(TextAlign.Center)
      } else {
        Image(content.url)
          .draggable(false)
          .height(this.options.imageSize || IMAGE_DEFAULT)
          .width((this.options.imageSize || IMAGE_DEFAULT))
        Text(content.text)
          .textAlign(TextAlign.Center)
          .width(this.blockWidth)
          .fontSize($r('sys.float.ohos_id_text_size_button3'))
          .padding({ top: 2, left: TEXT_PADDING_LEFT_RIGHT, right: TEXT_PADDING_LEFT_RIGHT })
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .textAlign(TextAlign.Center)
      }
      if (type === 'add') {
        Image($r("sys.media.ohos_ic_public_add_norm_filled"))
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
            x: this.blockWidth - 16,
            y: -18
          })
          .onClick(() => {
            if (this.clickAddBtn) return
            this.scaleIcon = 0
            this.content = content
            const index = this.unSelected.findIndex(i => i.id === content.id)
            this.editGridDataLength = this.selected.length + 1
            const endPosition = this.getEditItemGridPosition(this.selected, index)
            this.unSelectedIndex = index
            this.endX = endPosition.x
            this.endY = endPosition.y

            this.clickAddBtn = true
            this.arrayUnSelectIsChange = 1
            setTimeout(() => {
              this.scaleIcon = 1
              this.arrayUnSelectIsChange = 2
              this.selected.push(content);
              this.unSelected.splice(index, 1)
              this.endX = 0
              this.endY = 0
              if (!this.gridComState) {
                this.onSaveEdit()
              }
              this.clickAddBtn = false
            }, DURATION)
          })
      }

      Image($r("sys.media.ohos_ic_public_remove_filled"))
        .fillColor($r("sys.color.ohos_id_color_secondary"))
        .visibility(type === "delete" && this.gridComState ? 0 : 1)
        .width(ICON_SIZE)
        .height(ICON_SIZE)
        .opacity(type === "delete" && this.gridComState ? 1 : 0)
        .transition({ type: TransitionType.All, scale: { x: 0, y: 0 } })
        .position({
          x: state && content.id === this.content.id ? this.blockWidth - 17 : this.blockWidth - 16,
          y: -18
        })
        .animation({
          duration: DURATION,
          curve: Curve.Linear,
          iterations: 1,
          playMode: PlayMode.Normal,
        })
        .onClick(() => this.handleDeleteClick(content))
    }
    .backgroundColor(this.isTouchDown && content.id === this.content.id ? this.touchDown : '')
    .colorBlend(this.isTouchDown && content.id === this.content.id ? this.touchDownBg : '')
    .scale(content.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {})
    .animation({
      duration: 500,
      curve: curves.springCurve(10, 1, 410, 38)
    })
    .clip(false)
    .width(this.blockWidth)
    .height(this.blockWidth)
    .zIndex(999)
    .padding({
      top: TEXT_PADDING_LEFT_RIGHT,
      bottom: 8,
    })
  }

  @Builder
  TextBlockBuilder(content: GridObjectSortComponentItem, type?: string) {
    Stack() {
      Text(content.text)
        .blockTextStyle(this.blockWidth)
        .maxLines(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .textAlign(TextAlign.Center)
        .backgroundColor(this.isTouchDown && content.id === this.content.id ? this.touchDown : $r('sys.color.ohos_id_color_button_normal'))
        .colorBlend(this.isTouchDown && content.id === this.content.id ? this.touchDownBg : '')
        .scale(this.gridComState ? { x: this.scaleGridItemNinetyPercent, centerX: 0 } : { x: this.scaleGridItemNinetyPercent })
        .animation({
          duration: 250,
          curve: curves.springCurve(0, 1, 400, 38),
          iterations: 1,
          playMode: PlayMode.Normal,
        })
      // 删除图标
      Image($r("sys.media.ohos_ic_public_remove_filled"))
        .transition({ type: TransitionType.All, scale: { x: 0, y: 0, centerX: 10, centerY: 16 } })
        .scale(content.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon } : {})
        .visibility(type === "delete" && this.gridComState ? 0 : 1)
        .fillColor($r("sys.color.ohos_id_color_secondary"))
        .width(ICON_SIZE)
        .position({
          x: type === "delete" && this.gridComState ? (this.blockWidth * this.scaleGridItemNinetyPercent) - 16 : this.blockWidth - 16,
          y: type === "delete" && this.gridComState ? -5 : -8
        })
        .animation({
          duration: 250,
          curve: COMMON_BEZIER,
          iterations: 1,
          playMode: PlayMode.Normal,
        })
        .onClick(() => this.handleDeleteClick(content))
    }
    .scale(content.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {})
    .animation({
      duration: 500,
      curve: curves.springCurve(10, 1, 410, 38),
      iterations: 1,
      playMode: PlayMode.Normal,
    })
    .height(28)
  }

  @Builder
  AddTagBuilder() {
    Grid() {
      ForEach(this.unSelected, (item: GridObjectSortComponentItem, index: number) => {
        GridItem() {
          Stack() {
            if (this.options.type === GridObjectSortComponentType.IMAGE_TEXT) {
              this.ImageTextBuilder(item, "add")
            } else {
              Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
                if (!(this.addIconShow && item.id === this.content.id)) {
                  Image($r("sys.media.ic_public_add"))
                    .fillColor($r('sys.color.ohos_id_color_text_secondary'))
                    .width(16)
                    .margin({ right: 4 })
                }
                Text(item.text)
                  .fontSize($r('sys.float.ohos_id_text_size_button3'))
                  .width(this.blockWidth - 24)
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .textAlign(TextAlign.Center)
                  .height('100%')

                if (this.gridComState && this.addIconShow && item.id === this.content.id) {
                  Image($r("sys.media.ohos_ic_public_remove_filled"))
                    .transition({ scale: { x: 0, y: 0 } })
                    .fillColor($r("sys.color.ohos_id_color_secondary"))
                    .width(ICON_SIZE)
                    .position({
                      x: this.blockWidth - 32,
                      y: -4
                    })
                }

              }
              .backgroundColor(this.isTouchDown && item.id === this.content.id ? this.touchDown : $r('sys.color.ohos_id_color_button_normal'))
              .borderRadius(50)
              .width(this.blockWidth)
              .height(28)
              .padding({
                left: TEXT_PADDING_LEFT_RIGHT,
                right: TEXT_PADDING_LEFT_RIGHT,
              })
            }
          }
          .scale(this.isTouchDown && item.id === this.content.id ? {
                                                                     x: this.scaleAddItemNinetyPercent,
                                                                     y: this.scaleAddItemNinetyPercent
                                                                   } : { x: 1, y: 1 })
          .animation({
            duration: DURATION,
            curve: curves.springCurve(0, 1, 150, 24),
            iterations: 1,
            playMode: PlayMode.Normal,
          })
          .margin({
            top: 2,
            bottom: 16
          })
          .onTouch((event: TouchEvent) => {
            if (event.type === TouchType.Down) {
              this.content = item
              this.isTouchDown = true
              this.scaleAddItemNinetyPercent = 0.9
            }
            if (event.type === TouchType.Up) {
              animateTo({
                duration: DURATION,
                curve: COMMON_BEZIER
              }, () => {
                this.addIconShow = true
              })
              this.isTouchDown = false
              this.scaleAddItemNinetyPercent = 1
              if (this.clickAddBtn || (!this.gridComState && this.options.type === GridObjectSortComponentType.IMAGE_TEXT)) return
              if(this.options.type === GridObjectSortComponentType.TEXT)
              {
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
                this.arrayUnSelectIsChange = 2
                this.selected.push(item);
                this.unSelected.splice(index, 1)

                this.endX = 0
                this.endY = 0
                this.clickAddBtn = false
                if (!this.gridComState) {
                  this.onSaveEdit()
                }
                animateTo({
                  duration: DURATION,
                  curve: COMMON_BEZIER }, () => {
                  this.addIconShow = false
                })
              }, DURATION)
            }
          })
          .gesture(
            LongPressGesture({ repeat: true })
              .onAction((event: GestureEvent) => {
                if (!this.gridComState) {
                  animateTo({ duration: DURATION }, () => {
                    this.gridComState = true
                  })
                }
              })
          )
        }
        .clip(false)
        .padding({
          left: 8,
          right: 8
        })
        .translate({
          x: this.getUnSelectXY(this.unSelected, index, this.unSelectedIndex).x,
          y: this.getUnSelectXY(this.unSelected, index, this.unSelectedIndex).y,
        })
        .animation({
          duration: DURATION,
          curve: curves.springCurve(0, 1, 150, 24),
          iterations: 1,
          playMode: PlayMode.Normal,
        })
      })
    }
    .columnsTemplate(this.customColumnsTemplate())
    .padding({
      top: 8,
      left: 16,
      right: 16,
    })
    .clip(false)
    .height(this.getGridHeight(this.unSelected) + 120)
  }

  @Builder
  EditTagBuilder() {
    Grid() {
      ForEach(this.selected, (select: GridObjectSortComponentItem, index: number) => {
        GridItem() {
          Stack() {
            if (this.options.type === GridObjectSortComponentType.IMAGE_TEXT) {
              this.ImageTextBuilder(select, 'delete')
            } else {
              this.TextBlockBuilder(select, 'delete')
            }
          }
          .clip(false)
          .margin({
            top: 2,
            bottom: 16
          })
          .onTouch((event: TouchEvent) => {
            if (event.type === TouchType.Down) {
              this.content = select
              this.isTouchDown = true
            }

            if (event.type === TouchType.Up) {
              this.isTouchDown = false
              this.longScaleOnePointTwo = 1
            }
          })
        }
        .clip(false)
        .translate({
          x: this.getXY(this.selected, index, this.selectedIndex).x,
          y: this.getXY(this.selected, index, this.selectedIndex).y,
        })
        .animation({
          duration: DURATION,
          curve: COMMON_BEZIER,
          iterations: 1,
          playMode: PlayMode.Normal,
        })
      })
    }
    .parallelGesture(
      LongPressGesture({ repeat: true })
        .onAction((event: GestureEvent) => {
          if (!this.gridComState) {
            this.scaleGridItemNinetyPercent = 0.9
            animateTo({ duration: DURATION }, () => {
              this.gridComState = true
            })
          } else {
            this.longScaleOnePointTwo = 1.2
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
      left: 16,
      right: 16,
      top: 8,
    })
    .height(this.selected.length === 0 && this.clickAddBtn ? this.blockHeight + 8 : this.getGridHeight(this.selected, 'edit'))
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
      this.longScaleOnePointTwo = 1
      this.isStartDrag = false
      this.selected.splice(insertIndex !== -1 ? insertIndex : this.selected.length - 1, 0, this.content)
    })
    .onItemDragMove((event: ItemDragInfo, itemIndex: number, insertIndex: number) => this.onDragMoveEvent(event, itemIndex, insertIndex))
  }

  build() {
    Column() {
      // header
      this.HeaderTitleBuilder()
      // main
      Scroll() {
        Column() {
          // top
          SubHeader({ secondaryTitle: this.options.showAreaTitle || $r('sys.string.ohos_grid_edit_subtitle_sort') })
          this.EditTagBuilder()
          // bottom
          SubHeader({ secondaryTitle: this.options.addAreaTitle || $r('sys.string.ohos_grid_edit_subtitle_add') })
          this.AddTagBuilder()
        }
        .onAreaChange((oldValue: Area, newValue: Area) => {
          this.areaWidth = Math.trunc(Number(newValue.width));
          this.blockWidth = this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? this.getImageBlockWidth() : this.getBlockWidth()
        }).width("100%")
      }
    }
    .width('100%')
    .height('90%')
  }
}
