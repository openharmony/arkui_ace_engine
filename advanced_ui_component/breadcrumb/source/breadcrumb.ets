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

import measure from '@ohos.measure'

export interface LabelInfo {
  text: string,
  icon?: ResourceStr
}

@Component
export struct Breadcrumb {
  selfWidth: number = 0;
  @Link @Watch('onInfoChanged') labelInfo : Array<LabelInfo>;
  @State labels : Array<LabelInfo> = [];
  onLabelClick: (index: number, event: ClickEvent) => void = undefined;
  onLabelDragStart: (index: number, event: DragEvent) => CustomBuilder | DragItemInfo = undefined;
  onLabelDragEnter: (index: number, event: DragEvent) => void = undefined;
  onLabelDragLeave: (index: number, event: DragEvent) => void = undefined;
  onLabelDrop: (index: number, event: DragEvent) => void = undefined;
  onLabelDragCancel: (event: DragEvent) => void = undefined;

  @State hasMenu: boolean = false;
  @State menuInfo: Array<LabelInfo> = [];
  @State hiddenLabels: Array<number> = [];
  @State bgColor: Resource = $r('sys.color.ohos_id_color_background_transparent');
  @State showMenu: boolean = false;
  @State hoverIndex: number = -1;

  timerId: number = - 1;
  scroller: Scroller = new Scroller();

  labelWidths: Array<number> = []; // current width of each label.
  originalLabelWidth: Array<number> = []; // max width of each label.
  firstLevelLabelWidth: number = 0; // the first level label width.
  secondLevelLabelWidth: number = 0; // the second level label width.
  thirdLevelLabelWidth: number = 0; // the third level label width.
  totalFourthLevelLength: number = 0; // the total fourth level labels width (include separator icon).
  menuButtonWidth: number = 0; // the menu button width.
  idealTotalLength: number = 0; // the total labels max width (include separator icon).
  minLabelWidth: Array<number> = []; // minimal width of each label.
  minFourthLevelLabelLength: number = 0; // the total min width of the fourth level labels.
  minLabelLengthWithoutFourthLevel: number = 0; // the total min width of the first, second, third level labels.
  separatorIconWidth: number = 20; // the separator icon length (12vp + left padding: 4vp + right padding: 4vp).
  labelPadding: number = 16; // left padding: 8vp + right padding: 8vp
  iconWidth: number = 24; // the icon width of label.
  labelSpace: number = 4 // the space of icon and text in label.

  // when the info length changed, update all the data.
  onInfoChanged() {
    if (!this.labelInfo) {
      return;
    }

    if (JSON.stringify(this.labelInfo) === JSON.stringify(this.labels)) {
      return;
    }
    this.labels = [];
    this.labels = this.labelInfo.slice(0, this.labelInfo.length);
    this.checkLabelInfo();

    this.initData();
  }

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void {
    let pos = 0;
    children.forEach((child, index) => {
      child.layout({x: pos, y: 0})
      pos += child.measureResult.width as number;
    })
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
                constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: constraint.maxWidth as number, height: constraint.maxHeight as number }

    if (!this.labels || this.labels.length <= 0) {
      return sizeResult;
    }
    this.selfWidth = px2vp(constraint.maxWidth as number)
    this.clearMenu();
    if (this.labels.length === 1) {
      this.measureWithOneLabel();
    } else if (this.labels.length === 2) {
      this.measureWithTwoLabels();
    } else if (this.labels.length === 3) {
      this.measureWithThreeLabels();
    } else {
      this.measureWithManyLabels();
    }

    children.forEach((child, index) => {
      let childWidth: number;
      if (index === 0) {
        childWidth = this.labelWidths[index]
      } else if (index === 2) {
        childWidth = this.hasMenu ? this.menuButtonWidth : 0
      } else if (index % 2 === 0) {
        childWidth = this.labelWidths[index / 2 - 1]
      } else {
        let arrowWidth = 0;
        if (index === 3) {
          arrowWidth = this.hasMenu ? this.separatorIconWidth : 0;
        } else {
          arrowWidth = this.labelWidths[(index - 3) / 2] === 0 ? 0 : this.separatorIconWidth;
        }
        childWidth = arrowWidth
      }
      child.measure({minWidth: childWidth, maxWidth: childWidth});
    })
    return sizeResult
  }

  measureWithManyLabels() {
    this.menuInfo = [];
    this.hiddenLabels = [];
    for (let i = 0; i < this.labels.length; i++) {
      this.labelWidths[i] = this.originalLabelWidth[i];
    }
    let allFourthLevelLabel = this.selfWidth -
      (this.firstLevelLabelWidth + this.secondLevelLabelWidth + this.thirdLevelLabelWidth) - this.separatorIconWidth * 2;
    if (this.minFourthLevelLabelLength <= allFourthLevelLabel && allFourthLevelLabel < this.totalFourthLevelLength) {
      // Only compress the fourth level label without adding it to the menu
      this.compressFourthLevelLabelWithoutMenu(allFourthLevelLabel);
    } else if (this.minFourthLevelLabelLength > allFourthLevelLabel &&
      this.selfWidth > this.minLabelLengthWithoutFourthLevel + this.menuButtonWidth + this.separatorIconWidth) {
      if (allFourthLevelLabel >= this.menuButtonWidth + this.separatorIconWidth) {
        // Add label to the menu one by one and compress the remaining labels to continue
        this.compressFourthLevelLabelWithMenu(allFourthLevelLabel);
      } else {
        // Add all the fourth level labels to the menu and continue compressing the remaining labels
        this.measureWithThreeLabels();
      }
    } else if (this.selfWidth <=
      this.minLabelLengthWithoutFourthLevel + this.menuButtonWidth + this.separatorIconWidth) {
      // Directly set all labels to the minimum width
      this.compressToLessMinTotalWidth();
    } else if (this.selfWidth >= this.idealTotalLength) {
      // Directly set all labels to the maximum  width
      this.resetToOriginalWidth();
    }
  }

  measureWithOneLabel() {
    if (this.selfWidth >= this.firstLevelLabelWidth) {
      this.labelWidths[0] = this.firstLevelLabelWidth;
    } else if (this.selfWidth >= this.minLabelWidth[0]) {
      this.labelWidths[0] = this.selfWidth;
    } else {
      this.labelWidths[0] = this.minLabelWidth[0];
    }
  }

  measureWithTwoLabels() {
    this.labelWidths[1] = this.firstLevelLabelWidth;
    this.labelWidths[0] = this.secondLevelLabelWidth;

    let totalWidth = this.firstLevelLabelWidth + this.secondLevelLabelWidth + this.separatorIconWidth;
    let difference = totalWidth - this.selfWidth
    let reducedLength = 0;
    if (difference > 0) {
      reducedLength = (this.secondLevelLabelWidth - difference) >= this.minLabelWidth[0] ?
        difference : this.secondLevelLabelWidth - this.minLabelWidth[0];
      this.labelWidths[0] -= reducedLength;
      difference -= reducedLength;
    } else {
      return;
    }

    if (difference > 0) {
      reducedLength = (this.firstLevelLabelWidth - difference) >= this.minLabelWidth[1] ?
        difference : this.firstLevelLabelWidth - this.minLabelWidth[1];
      this.labelWidths[1] -= reducedLength;
      difference -= reducedLength;
    } else {
      this.labelWidths[1] = this.firstLevelLabelWidth;
    }
  }

  measureWithThreeLabels() {
    let selfLength = 0;
    if (this.labels.length === 3) {
      selfLength = this.selfWidth;
    } else {
      if (!this.hasMenu) {
        this.hasMenu = true;
      }
      for (let i = 1; i < this.labels.length - 2; i++) {
        this.menuInfo.push(this.labels[i]);
        this.hiddenLabels.push(i);
        this.labelWidths[i] = 0;
      }

      selfLength = this.selfWidth - this.menuButtonWidth - this.separatorIconWidth;
    }
    this.labelWidths[this.labels.length - 1] = this.firstLevelLabelWidth;
    this.labelWidths[this.labels.length - 2] = this.secondLevelLabelWidth;
    this.labelWidths[0] = this.thirdLevelLabelWidth;

    let totalWidth = this.thirdLevelLabelWidth + this.firstLevelLabelWidth +
      this.secondLevelLabelWidth + this.separatorIconWidth * 2;
    let difference = totalWidth - selfLength;
    let reducedLength = 0;
    if (difference > 0) {
      reducedLength = (this.thirdLevelLabelWidth - difference) >= this.minLabelWidth[0] ?
        difference : this.thirdLevelLabelWidth - this.minLabelWidth[0];
      this.labelWidths[0] -= reducedLength;
      difference -= reducedLength;
    } else {
      this.labelWidths[this.labels.length - 1] = this.firstLevelLabelWidth;
      this.labelWidths[this.labels.length - 2] = this.secondLevelLabelWidth;
      this.labelWidths[0] = this.thirdLevelLabelWidth;
      return;
    }

    if (difference > 0) {
      reducedLength = (this.secondLevelLabelWidth - difference) >= this.minLabelWidth[this.labels.length - 2] ?
        difference : this.secondLevelLabelWidth - this.minLabelWidth[this.labels.length - 2];
      this.labelWidths[this.labels.length - 2] -= reducedLength;
      difference -= reducedLength;
    } else {
      this.labelWidths[this.labels.length - 1] = this.firstLevelLabelWidth;
      this.labelWidths[this.labels.length - 2] = this.secondLevelLabelWidth;
      return;
    }

    if (difference > 0) {
      reducedLength = (this.firstLevelLabelWidth - difference) >= this.minLabelWidth[this.labels.length - 1] ?
        difference : this.firstLevelLabelWidth - this.minLabelWidth[this.labels.length - 1];
      this.labelWidths[this.labels.length - 1] -= reducedLength;
      difference -= reducedLength;
    } else {
      this.labelWidths[this.labels.length - 1] = this.firstLevelLabelWidth;
      return;
    }
  }

  clearMenu() {
    if (this.hasMenu) {
      this.hasMenu = false;
    }
    this.menuInfo = [];
    this.hiddenLabels = [];
  }

  compressFourthLevelLabelWithoutMenu(allFourthLevelLabel: number) {
    if (this.hasMenu) {
      this.hasMenu = false;
    }

    this.adjustFourthLevelLabelWidth(allFourthLevelLabel, 1);
  }

  compressFourthLevelLabelWithMenu(allFourthLevelLabel: number) {
    let nextAddInMenu = 1;
    this.menuInfo.push(this.labels[nextAddInMenu]);
    this.hiddenLabels.push(nextAddInMenu);
    if (!this.hasMenu) {
      this.hasMenu = true;
    }

    nextAddInMenu++;
    let isFinished = false;
    let curMinLength = 0;
    let preMinLength = 0;
    while (!isFinished) {
      for (let i = 1; i < nextAddInMenu; i++) {
        this.labelWidths[i] = 0;
      }

      for (let i = nextAddInMenu -1; i < this.labels.length - 2; i++) {
        if (i === nextAddInMenu - 1) {
          preMinLength += (this.minLabelWidth[i] + this.separatorIconWidth);
          continue;
        }
        preMinLength += (this.minLabelWidth[i] + this.separatorIconWidth);
        curMinLength += (this.minLabelWidth[i] + this.separatorIconWidth);
      }

      if (nextAddInMenu < this.labels.length - 2 &&
        curMinLength > allFourthLevelLabel - this.menuButtonWidth - this.separatorIconWidth) {
        this.menuInfo.push(this.labels[nextAddInMenu]);
        this.labelWidths[nextAddInMenu] = 0;
        this.hiddenLabels.push(nextAddInMenu);
        nextAddInMenu++;
        isFinished = false;
        preMinLength = 0;
        curMinLength = 0;
      } else if (preMinLength < allFourthLevelLabel - this.menuButtonWidth - this.separatorIconWidth &&
        nextAddInMenu > 2) {
        nextAddInMenu--;
        isFinished = false;
        this.menuInfo.pop();
        this.hiddenLabels.pop();
        preMinLength = 0;
        curMinLength = 0;
      } else {
        isFinished = true;
      }
    }

    let remainOriginalFourthLevel = 0;
    for (let i = nextAddInMenu; i < this.labels.length - 2; i++) {
      remainOriginalFourthLevel += (this.originalLabelWidth[i] + this.separatorIconWidth);
    }

    if (allFourthLevelLabel - this.menuButtonWidth - this.separatorIconWidth >= remainOriginalFourthLevel) {
      for (let i = nextAddInMenu; i < this.labels.length - 2; i++) {
        this.labelWidths[i] = this.originalLabelWidth[i];
      }
    } else {
      this.adjustFourthLevelLabelWidth(
        allFourthLevelLabel - this.menuButtonWidth - this.separatorIconWidth, nextAddInMenu);
    }

    this.labelWidths[0] = this.thirdLevelLabelWidth;
    this.labelWidths[this.labels.length - 2] = this.secondLevelLabelWidth;
    this.labelWidths[this.labels.length - 1] = this.firstLevelLabelWidth;
  }

  compressToLessMinTotalWidth() {
    this.hasMenu = true;
    this.labelWidths = [];
    for (let i = 0; i < this.labels.length; i++) {
      if (i === 0 || i === this.labels.length - 2 || i === this.labels.length - 1) {
        this.labelWidths.push(this.minLabelWidth[i]);
      } else {
        this.labelWidths.push(0);
        this.menuInfo.push(this.labels[i]);
        this.hiddenLabels.push(i);
      }
    }
  }

  resetToOriginalWidth() {
    this.labelWidths = [];
    for (let i = 0; i < this.labels.length; i++) {
      this.labelWidths.push(this.originalLabelWidth[i]);
    }
  }

  // Loop adjust the width of all four level labels
  adjustFourthLevelLabelWidth(allFourthLevelLabel: number, startIndex: number) {
    let realTotalFourthLevelWidth = 0;
    for (let i = startIndex; i < this.labels.length - 2; i++) {
      realTotalFourthLevelWidth += (this.originalLabelWidth[i] + this.separatorIconWidth);
      this.labelWidths[i] =  this.originalLabelWidth[i];
    }

    let maxLabelIndex :Array<number> = [];
    let maxWidth = 0;
    let secondWidth = 0;
    while(1) {
      for (let i = startIndex; i < this.labels.length - 2; i++) {
        if (maxWidth < this.labelWidths[i] && this.labelWidths[i] > this.minLabelWidth[i]) {
          maxWidth = this.labelWidths[i];
        }
      }

      for (let i = startIndex; i < this.labels.length - 2; i++) {
        if (secondWidth < this.labelWidths[i] && this.labelWidths[i] < maxWidth) {
          secondWidth = this.labelWidths[i];
        }
      }

      for (let i = startIndex; i < this.labels.length - 2; i++) {
        if (maxWidth === this.labelWidths[i] && this.labelWidths[i] > this.minLabelWidth[i]) {
          maxLabelIndex.push(i);
        }
      }

      if (maxLabelIndex.length === 0) {
        break;
      }

      let adjustWidth = maxWidth - (realTotalFourthLevelWidth - allFourthLevelLabel) / maxLabelIndex.length;
      if (adjustWidth >= secondWidth) {
        for (let i = 0; i < maxLabelIndex.length; i++) {
          if (adjustWidth >= this.minLabelWidth[maxLabelIndex[i]]) {
            this.labelWidths[maxLabelIndex[i]] = adjustWidth;
          } else {
            this.labelWidths[maxLabelIndex[i]] = this.minLabelWidth[maxLabelIndex[i]];
          }
        }
      } else {
        for (let i = 0; i < maxLabelIndex.length; i++) {
          this.labelWidths[maxLabelIndex[i]] = secondWidth;
        }
        maxWidth = secondWidth;
        secondWidth = 0;
        maxLabelIndex = [];
      }
      realTotalFourthLevelWidth = 0;
      for (let i = startIndex; i < this.labelWidths.length - 2; i++) {
        realTotalFourthLevelWidth += (this.labelWidths[i] + this.separatorIconWidth);
      }
      if (realTotalFourthLevelWidth - allFourthLevelLabel <= 0) {
        break;
      }
    }
  }

  initAllLabelWidth() {
    this.totalFourthLevelLength = 0;
    this.idealTotalLength = 0;
    this.labelWidths = [];
    this.originalLabelWidth = [];
    for (let i = 0; i < this.labels.length; i++) {
      let width = measure.measureText({
        textContent: this.labels[i].text
      });
      if (this.labels[i].icon) {
        this.labelWidths.push(px2vp(width) + this.labelPadding + this.iconWidth + this.labelSpace);
        this.originalLabelWidth.push(px2vp(width) + this.labelPadding + this.iconWidth + this.labelSpace);
        if (i === this.labels.length - 1) {
          this.idealTotalLength += px2vp(width) + this.labelPadding + this.iconWidth + this.labelSpace;
        } else {
          this.idealTotalLength += px2vp(width) + this.labelPadding + this.iconWidth +
            this.labelSpace + this.separatorIconWidth;
        }

        if (i > 0 && i < this.labels.length - 2) {
          this.totalFourthLevelLength += (px2vp(width) + this.labelPadding + this.iconWidth +
            this.labelSpace + this.separatorIconWidth);
        }
      } else {
        this.labelWidths.push(px2vp(width) + this.labelPadding);
        this.originalLabelWidth.push(px2vp(width) + this.labelPadding);
        if (i === this.labels.length - 1) {
          this.idealTotalLength += px2vp(width) + this.labelPadding;
        } else {
          this.idealTotalLength += px2vp(width) + this.separatorIconWidth + this.labelPadding;
        }

        if (i > 0 && i < this.labels.length - 2) {
          this.totalFourthLevelLength += (px2vp(width) + this.separatorIconWidth + this.labelPadding);
        }
      }
    }
  }

  initAllMinWidth() {
    this.minFourthLevelLabelLength = 0;
    this.minLabelLengthWithoutFourthLevel = 0;
    this.minLabelWidth = [];
    let minWidth = 0
    for (let i = 0; i < this.labels.length; i++) {
      if (this.labels[i].icon) {
        minWidth = this.menuButtonWidth;
      } else {
        minWidth = px2vp(measure.measureText({
          textContent: '我…',
        })) + this.labelPadding;
      }

      this.minLabelWidth.push(minWidth);
      if (i > 0 && i < this.labels.length - 2) {
        this.minFourthLevelLabelLength += (minWidth + this.separatorIconWidth);
      } else {
        this.minLabelLengthWithoutFourthLevel += (minWidth + this.separatorIconWidth);
      }
    }
  }

  initNotFourthLevelWidth() {
    if (this.labels.length > 0) {
      if (this.labels[this.labels.length - 1].icon) {
        this.firstLevelLabelWidth = px2vp(measure.measureText({
          textContent: this.labels[this.labels.length - 1].text
        })) + this.labelPadding + this.iconWidth + this.labelSpace;
      } else {
        this.firstLevelLabelWidth = px2vp(measure.measureText({
          textContent: this.labels[this.labels.length - 1].text
        })) + this.labelPadding;
      }
    }

    if (this.labels.length > 1) {
      if (this.labels[this.labels.length - 2].icon) {
        this.secondLevelLabelWidth = px2vp(measure.measureText({
          textContent: this.labels[this.labels.length - 2].text
        })) + this.labelPadding + this.iconWidth + this.labelSpace;
      } else {
        this.secondLevelLabelWidth = px2vp(measure.measureText({
          textContent: this.labels[this.labels.length - 2].text
        })) + this.labelPadding;
      }
    }

    if (this.labels.length > 2) {
      if (this.labels[0].icon) {
        this.thirdLevelLabelWidth = px2vp(measure.measureText({
          textContent: this.labels[0].text
        })) + this.labelPadding + this.iconWidth + this.labelSpace;
      } else {
        this.thirdLevelLabelWidth = px2vp(measure.measureText({
          textContent: this.labels[0].text
        })) + this.labelPadding;
      }
    }
  }

  initData() {
    this.initAllLabelWidth();
    this.initAllMinWidth();
    this.initNotFourthLevelWidth();
  }

  checkLabelInfo() {
    for (let i = 0; i < this.labels.length; i++) {
      if (!this.labels[i]) {
        this.labels[i] = {text: 'undefined'};
      }
      if (!this.labels[i].text || this.labels[i].text === '') {
        this.labels[i].text = 'undefined';
      }
    }
  }

  aboutToAppear() {
    if (!this.labelInfo) {
      return;
    }

    this.labels = [];
    this.labels = this.labelInfo.slice(0, this.labelInfo.length);

    this.checkLabelInfo();
    this.menuButtonWidth = px2vp(measure.measureText({
      textContent: '···'
    })) + this.labelPadding;
    this.initData();
  }

  @Builder menu() {
    Scroll(this.scroller) {
      Menu() {
        ForEach(this.menuInfo, (item, index) => {
          MenuItem({ startIcon: item.icon, content: item.text })
            .key(index === 0 ? 'menu' : null)
            .onClick((event: ClickEvent) => {
              if (!this.onLabelClick) {
                return;
              }
              this.onLabelClick(this.labels.indexOf(item), event)
              this.showMenu = !this.showMenu
            })
            .onDragStart((event: DragEvent, extraParams: string) => {
              if (!this.onLabelDragStart) {
                return;
              }
              return this.onLabelDragStart(this.labels.indexOf(item), event)
            })
            .onDragEnter((event: DragEvent, extraParams: string) => {
              if (!this.onLabelDragEnter) {
                return;
              }
              this.onLabelDragEnter(this.labels.indexOf(item), event)
            })
            .onDragLeave((event: DragEvent, extraParams: string) => {
              if (!this.onLabelDragLeave) {
                return;
              }
              this.onLabelDragLeave(this.labels.indexOf(item), event)
            })
            .onDrop((event: DragEvent, extraParams: string) => {
              if (this.showMenu) {
                this.showMenu = false
              }

              if (!this.onLabelDrop) {
                return;
              }
              this.onLabelDrop(this.labels.indexOf(item), event)
            })
        })
      }
    }
    .onDragLeave((event: DragEvent, extraParams: string) => {
      this.showMenu = false
    })
    .onDrop(() => {})
    .borderRadius($r('sys.float.ohos_id_corner_radius_card'))
  }

  @Styles focusStyles() {
    .borderColor($r('sys.color.ohos_id_color_focused_outline'))
  }

  @Styles normalStyles() {
    .borderColor(Color.Transparent)
  }

  @Builder breadcrumbBuilder() {
    ForEach(this.labels, (item, index) => {
      if (index < this.labels.length - 1) {
        Button() {
          Row({space: 4}) {
            if (item.icon) {
              Image(item.icon)
                .width(24)
                .height(24)
            }
            Text(item.text)
              .fontSize($r('sys.float.ohos_id_text_size_body1'))
              .focusable(this.hiddenLabels.indexOf(index) === -1 ? true : false)
              .fontColor($r('sys.color.ohos_id_color_text_secondary'))
              .textOverflow({overflow: this.hoverIndex === index ? TextOverflow.MARQUEE : TextOverflow.Ellipsis})
              .maxLines(1)
              .layoutWeight(1)
          }
          .padding({left: 6, right: 6})
          .clip(true)
        }
        .borderWidth(2)
        .clip(true)
        .type(ButtonType.Normal)
        .backgroundColor(this.bgColor)
        .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
        .height(40)
        .stateStyles({
          focused: this.focusStyles,
          normal: this.normalStyles
        })
        .onHover((isHover: boolean) => {
          this.hoverIndex = isHover ? index : -1;
        })
        .onClick((event: ClickEvent) => {
          if (!this.onLabelClick) {
            return;
          }
          if (index === 1 && this.hasMenu) {

            return
          }
          this.onLabelClick(index, event)
        })
        .onDragStart((event: DragEvent, extraParams: string) => {
          if (!this.onLabelDragStart) {
            return;
          }
          return this.onLabelDragStart(index, event)
        })
        .onDragEnter((event: DragEvent, extraParams: string) => {
          if (this.showMenu) {
            this.showMenu = false
          }
          if (!this.onLabelDragEnter) {
            return;
          }
          this.onLabelDragEnter(index, event)
        })
        .onDragLeave((event: DragEvent, extraParams: string) => {
          if (!this.onLabelDragLeave) {
            return;
          }
          this.onLabelDragLeave(index, event)
        })
        .onDrop((event: DragEvent, extraParams: string) => {
          if (!this.onLabelDrop) {
            return;
          }
          if (index === this.labels.length - 1 && this.onLabelDragCancel) {
            this.onLabelDragCancel(event)
          } else {
            this.onLabelDrop(index, event)
          }
        })

        Stack() {
          Image($r('sys.media.ohos_ic_public_arrow_right'))
            .width(12)
            .height(24)
            .margin({top: 8, bottom: 8, left: 4, right: 4})
            .fillColor($r('sys.color.ohos_id_color_tertiary'))
        }
        .clip(true)

        if (index === 0) {
          Button() {
            Stack() {
              Text('···').fontSize($r('sys.float.ohos_id_text_size_body1'))
                .focusable(this.hasMenu ? true : false)
                .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                .maxLines(1)
            }
            .padding({left: 6, right: 6})
          }
          .height(40)
          .clip(true)
          .type(ButtonType.Normal)
          .borderWidth(2)
          .backgroundColor(this.bgColor)
          .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
          .stateStyles({
            focused: this.focusStyles,
            normal: this.normalStyles
          })
          .backgroundColor(this.bgColor)
          .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
          .height(40)
          .onClick(() => {
            this.showMenu = !this.showMenu
          })
          .onDragEnter((event: DragEvent, extraParams: string) => {
            if (!this.showMenu && this.labels.indexOf(this.menuInfo[0]) === this.hiddenLabels[0]) {
              this.menuInfo.reverse();
            }
            this.timerId = setInterval(() => {
              if (!this.showMenu) {
                this.showMenu = true
              }
              clearInterval(this.timerId)
            }, 1000)
          })
          .onDragLeave((event: DragEvent, extraParams: string) => {
            clearInterval(this.timerId)
          })
          .onDrop(() => {})
          .onKeyEvent((event: KeyEvent) => {
            if (event.type === KeyType.Up && event.keyCode === 2050) {
              focusControl.requestFocus('menu')
            }
          })
          .bindPopup(this.showMenu, {
            builder: this.menu,
            enableArrow: false,
            onStateChange: (e) => {
              if (!e.isVisible) {
                if (this.labels.indexOf(this.menuInfo[0]) != this.hiddenLabels[0]) {
                  this.menuInfo.reverse();
                }
                this.showMenu = false
              }
            }
          })

          Stack() {
            Image($r('sys.media.ohos_ic_public_arrow_right'))
              .width(12)
              .height(24)
              .margin({top: 8, bottom: 8, left: 4, right: 4})
              .fillColor($r('sys.color.ohos_id_color_tertiary'))
          }
          .clip(true)
        }
      } else {
        Row({space: 4}) {
          if (item.icon) {
            Image(item.icon)
              .width(24)
              .height(24)
              .margin({left: 6})
          }

          Text(item.text)
            .fontSize($r('sys.float.ohos_id_text_size_body1'))
            .fontColor($r('sys.color.ohos_id_color_text_primary'))
            .textOverflow({overflow: this.hoverIndex === index ? TextOverflow.MARQUEE : TextOverflow.Ellipsis})
            .maxLines(1)
            .margin({left: item.icon ? 0 : 8, right: 8})
            .layoutWeight(1)
        }
        .backgroundColor(this.bgColor)
        .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
        .height(40)
        .onHover((isHover: boolean) => {
          this.hoverIndex = isHover ? index : -1;
        })
        .onDragStart((event: DragEvent, extraParams: string) => {
          if (!this.onLabelDragStart) {
            return;
          }
          return this.onLabelDragStart(index, event)
        })
        .onDragEnter((event: DragEvent, extraParams: string) => {
          if (!this.onLabelDragEnter) {
            return;
          }
          this.onLabelDragEnter(index, event)
        })
        .onDragLeave((event: DragEvent, extraParams: string) => {
          if (!this.onLabelDragLeave) {
            return;
          }
          this.onLabelDragLeave(index, event)
        })
        .onDrop((event: DragEvent, extraParams: string) => {
          if (!this.onLabelDrop) {
            return;
          }

          if (index === this.labels.length - 1 && this.onLabelDragCancel) {
            this.onLabelDragCancel(event)
          } else {
            this.onLabelDrop(index, event)
          }
        })
      }
    }, (item, index) => item.text + item.icon + index)
  }

  build() {
    this.breadcrumbBuilder()
  }
}