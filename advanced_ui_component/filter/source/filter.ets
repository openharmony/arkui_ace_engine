/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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
import curves from '@ohos.curves'

const TEXT_HOT_AREA_WIDTH: number = 8
const LIST_ROW_HEIGHT: number = 40
const ARROW_IMG_SIZE: number = 24
const MULTI_LINE_PADDING: number = 24
const BAR_ANIMATION_DURATION: number = 150
const ARROW_ANIMATION_DURATION: number = 200
const ANIMATION_DURATION_250: number = 250
const ANIMATION_DURATION_100: number = 100
const FILTER_TOP_PADDING: number = 8
const SEPARATOR_HEIGHT: number = 16
const SEPARATOR_WIDTH: number = 1
const FLOAT_OPACITY: number = 0.95
const FILTER_FONT_SIZE = 12
const FOCUS_BORDER_WIDTH = 2
const ARROW_SHOW_DELAY = 300
const PERCENT_100: Length = '100%'
const SHARP_CUBIC_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1)
const INTER_POLATING_SPRING = curves.interpolatingSpring(0, 1, 328, 34)
const FRICTION_CUBIC_BEZIER = curves.cubicBezierCurve(0.2, 0, 0.2, 1)
const TRANS_COLOR: string = '#00FFFFFF'

export enum FilterType {
  MULTI_LINE_FILTER,
  LIST_FILTER
}

export declare type FilterParams = {
  name: ResourceStr,
  options: Array<ResourceStr>
}

export declare type FilterResult = {
  name: ResourceStr,
  index: number,
  value: ResourceStr
}

@Observed
class FontWeightArray extends Array<FontWeight> {
}

@Observed
class ResourceArray extends Array<Resource> {
}

@Observed
class BooleanArray extends Array<boolean> {
}

@Observed
export class ObservedBoolean {
  public value: boolean

  constructor(value: boolean) {
    this.value = value
  }
}

@Observed
class ObservedNumber {
  public value: number

  constructor(value: number) {
    this.value = value
  }
}

@Component
struct ListFilterRow {
  @ObjectLink colorRow: ResourceArray
  @ObjectLink fontWeightRow: FontWeightArray
  @ObjectLink backgroundColorRow: ResourceArray
  @ObjectLink isBackgroundHoverRow: BooleanArray
  filterRow: FilterParams
  onItemClick: (colIndex: number) => void

  build() {
    List() {
      ForEach(this.filterRow.options, (option, colIndex?: number) => {
        ListItem() {
          Text(option.toString())
            .fontSize($r('sys.float.ohos_id_text_size_body3'))
            .fontColor(this.colorRow[colIndex])
            .fontWeight(this.fontWeightRow[colIndex])
            .focusable(true)
        }
        .height(PERCENT_100)
        .onClick(() => {
          this.onItemClick(colIndex)
        })
        .focusable(true)
        .stateStyles({
          focused: {
            .border({
              radius: $r('sys.float.ohos_id_corner_radius_clicked'),
              width: FOCUS_BORDER_WIDTH,
              color: $r('sys.color.ohos_id_color_focused_outline'),
              style: BorderStyle.Solid
            })
            .padding({
              left: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
              right: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH
            })
          },
          normal: {
            .border({
              radius: $r('sys.float.ohos_id_corner_radius_clicked'),
              width: 0 })
            .padding({ left: TEXT_HOT_AREA_WIDTH, right: TEXT_HOT_AREA_WIDTH })
          }
        })
        .backgroundColor(this.isBackgroundHoverRow[colIndex] ? this.backgroundColorRow[colIndex] : TRANS_COLOR)
        .onHover((isHover: boolean) => {
          animateTo({
            curve: FRICTION_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_250
          }, () => {
            if (isHover) {
              this.backgroundColorRow[colIndex] = $r('sys.color.ohos_id_color_hover')
              this.isBackgroundHoverRow[colIndex] = true
            } else {
              this.isBackgroundHoverRow[colIndex] = false
            }
          })
        })
        .onTouch((event) => {
          if (event.type === TouchType.Down) {
            animateTo({
              curve: SHARP_CUBIC_BEZIER,
              duration: ANIMATION_DURATION_100
            }, () => {
              this.backgroundColorRow[colIndex] = $r('sys.color.ohos_id_color_click_effect')
              this.isBackgroundHoverRow[colIndex] = true
            })
          } else if (event.type === TouchType.Up) {
            animateTo({
              curve: SHARP_CUBIC_BEZIER,
              duration: ANIMATION_DURATION_100
            }, () => {
              this.isBackgroundHoverRow[colIndex] = false
            })
          }
        })
      })
    }
    .listDirection(Axis.Horizontal)
    .margin({ left: -TEXT_HOT_AREA_WIDTH * 2 })
    .scrollBar(BarState.Off)
    .width(PERCENT_100)
    .height(LIST_ROW_HEIGHT)
    .align(Alignment.Start)
  }
}

@Component
struct MultiFilterRow {
  @ObjectLink colorRow: ResourceArray
  @ObjectLink fontWeightRow: FontWeightArray
  @ObjectLink backgroundColorRow: ResourceArray
  @ObjectLink isBackgroundHoverRow: BooleanArray
  @ObjectLink twoLineModeItemNumRow: ObservedNumber
  @ObjectLink twoLineModeItemNumRecordRow: ObservedNumber
  @ObjectLink arrowShowStateRow: ObservedBoolean
  @ObjectLink isArrowIconDown: ObservedBoolean
  filterRow: FilterParams = null
  onItemClick: (colIndex: number) => void
  @State arrowBgColorRow: Resource = $r('sys.color.ohos_id_color_hover')
  @State isArrowBgHoverRow: boolean = false
  private filterColumnWidth: number = 0

  private calcMultiFilterRowItemNum() {
    var curLineRetainWidth = this.filterColumnWidth - vp2px(MULTI_LINE_PADDING)
    var curLineSum = 0
    var curLine = 1
    for (var i = 0; i < this.filterRow.options.length; i++) {
      let option = this.filterRow.options[i]
      let itemWidth = measure.measureText({
        textContent: option,
        fontSize: FILTER_FONT_SIZE
      })
      if (i === 0) {
        continue
      } else {
        itemWidth += vp2px(TEXT_HOT_AREA_WIDTH * 2)
      }
      if (curLineRetainWidth - itemWidth > 0) {
        curLineRetainWidth -= itemWidth
        curLineSum += 1
      } else {
        if (curLineSum === 0) {
          curLineSum++
          curLineRetainWidth = 0
        }
        if (curLine === 1) {
          curLine += 1
          curLineRetainWidth = this.filterColumnWidth - vp2px(ARROW_IMG_SIZE) - vp2px(MULTI_LINE_PADDING)
          i--
        } else {
          break
        }
      }
    }
    return curLineSum
  }

  @Builder DownAndUpArrow() {
    Row() {
      Image(this.isArrowIconDown.value ? $r('sys.media.ohos_ic_public_arrow_down') : $r('sys.media.ohos_ic_public_arrow_up'))
        .width(ARROW_IMG_SIZE)
        .height(LIST_ROW_HEIGHT)
        .fillColor($r('sys.color.ohos_id_color_tertiary'))
        .focusable(true)
        .stateStyles({
          focused: {
            .border({
              radius: $r('sys.float.ohos_id_corner_radius_clicked'),
              width: FOCUS_BORDER_WIDTH,
              color: $r('sys.color.ohos_id_color_focused_outline'),
              style: BorderStyle.Solid
            })
            .width(ARROW_IMG_SIZE + FOCUS_BORDER_WIDTH * 2)
            .offset({ x: -FOCUS_BORDER_WIDTH })
          },
          normal: {
            .border({
              radius: $r('sys.float.ohos_id_corner_radius_clicked'),
              width: 0 })
            .width(ARROW_IMG_SIZE)
            .offset({ x: 0 })
          }
        })
    }
    .border({
      radius: $r('sys.float.ohos_id_corner_radius_clicked')
    })
    .height(LIST_ROW_HEIGHT)
    .width(ARROW_IMG_SIZE)
    .backgroundColor(this.isArrowBgHoverRow ? this.arrowBgColorRow : TRANS_COLOR)
    .focusable(true)
    .visibility(this.arrowShowStateRow.value ? Visibility.Visible : Visibility.Hidden)
    .onHover((isHover: boolean) => {
      animateTo({
        curve: FRICTION_CUBIC_BEZIER,
        duration: ANIMATION_DURATION_250
      }, () => {
        if (isHover) {
          this.arrowBgColorRow = $r('sys.color.ohos_id_color_hover')
          this.isArrowBgHoverRow = true
        } else {
          this.isArrowBgHoverRow = false
        }
      })
    })
    .onTouch((event) => {
      if (event.type === TouchType.Down) {
        animateTo({
          curve: SHARP_CUBIC_BEZIER,
          duration: ANIMATION_DURATION_100
        }, () => {
          this.arrowBgColorRow = $r('sys.color.ohos_id_color_click_effect')
          this.isArrowBgHoverRow = true
        })
      } else if (event.type === TouchType.Up) {
        animateTo({
          curve: SHARP_CUBIC_BEZIER,
          duration: ANIMATION_DURATION_100
        }, () => {
          this.isArrowBgHoverRow = false
        })
      }
    })
    .onClick(() => {
      if (this.isArrowIconDown.value) {
        this.isArrowIconDown.value = false
        this.arrowShowStateRow.value = false
        animateTo({
          curve: INTER_POLATING_SPRING,
        }, () => {
          this.twoLineModeItemNumRow.value = this.filterRow.options.length
        })

        animateTo({
          delay: 300,
          duration: ARROW_ANIMATION_DURATION,
          curve: SHARP_CUBIC_BEZIER
        }, () => {
          this.arrowShowStateRow.value = true
        })
      } else {
        this.isArrowIconDown.value = true
        this.arrowShowStateRow.value = false

        animateTo({
          curve: INTER_POLATING_SPRING,
        }, () => {
          this.twoLineModeItemNumRow.value = this.twoLineModeItemNumRecordRow.value
        })
        animateTo({
          delay: ARROW_SHOW_DELAY,
          duration: ARROW_ANIMATION_DURATION,
          curve: SHARP_CUBIC_BEZIER
        }, () => {
          this.arrowShowStateRow.value = true
        })
      }

    })

  }

  build() {
    Row() {
      if (this.filterRow.options && this.filterRow.options.length > 0) {
        Text(this.filterRow.options[0].toString())
          .height(LIST_ROW_HEIGHT)
          .width(px2vp(measure.measureText({
            textContent: this.filterRow.options[0].toString(),
            fontSize: FILTER_FONT_SIZE
          })) + (TEXT_HOT_AREA_WIDTH * 2))
          .margin({ left: -TEXT_HOT_AREA_WIDTH })
          .fontSize($r('sys.float.ohos_id_text_size_body3'))
          .fontColor(this.colorRow[0])
          .fontWeight(this.fontWeightRow[0])
          .backgroundColor(this.isBackgroundHoverRow[0] ? this.backgroundColorRow[0] : TRANS_COLOR)
          .onClick(() => {
            this.onItemClick(0)
          })
          .focusable(true)
          .onHover((isHover: boolean) => {
            animateTo({
              curve: FRICTION_CUBIC_BEZIER,
              duration: ANIMATION_DURATION_250
            }, () => {
              if (isHover) {
                this.backgroundColorRow[0] = $r('sys.color.ohos_id_color_hover')
                this.isBackgroundHoverRow[0] = true
              } else {
                this.isBackgroundHoverRow[0] = false
              }
            })
          })
          .onTouch((event) => {
            if (event.type === TouchType.Down) {
              animateTo({
                curve: SHARP_CUBIC_BEZIER,
                duration: ANIMATION_DURATION_100
              }, () => {
                this.backgroundColorRow[0] = $r('sys.color.ohos_id_color_click_effect')
                this.isBackgroundHoverRow[0] = true
              })
            } else if (event.type === TouchType.Up) {
              animateTo({
                curve: SHARP_CUBIC_BEZIER,
                duration: ANIMATION_DURATION_100
              }, () => {
                this.isBackgroundHoverRow[0] = false
              })
            }
          })
          .stateStyles({
            focused: {
              .border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: FOCUS_BORDER_WIDTH,
                color: $r('sys.color.ohos_id_color_focused_outline'),
                style: BorderStyle.Solid
              })
              .padding({
                left: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
                right: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH
              })
            },
            normal: {
              .border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: 0 })
              .padding({ left: TEXT_HOT_AREA_WIDTH, right: TEXT_HOT_AREA_WIDTH })
            }
          })
      }
      Row() {
        Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
          ForEach(this.filterRow.options.slice(0, this.twoLineModeItemNumRow.value + 1), (option, colIndex?: number) => {
            if (colIndex > 0) {
              Text(option.toString())
                .transition(TransitionEffect.OPACITY)
                .fontSize($r('sys.float.ohos_id_text_size_body3'))
                .height(LIST_ROW_HEIGHT)
                .fontColor(this.colorRow[colIndex])
                .fontWeight(this.fontWeightRow[colIndex])
                .backgroundColor(this.isBackgroundHoverRow[colIndex] ? this.backgroundColorRow[colIndex] : TRANS_COLOR)
                .onClick(() => {
                  this.onItemClick(colIndex)
                })
                .onHover((isHover: boolean) => {
                  animateTo({
                    curve: FRICTION_CUBIC_BEZIER,
                    duration: ANIMATION_DURATION_250
                  }, () => {
                    if (isHover) {
                      this.backgroundColorRow[colIndex] = $r('sys.color.ohos_id_color_hover')
                      this.isBackgroundHoverRow[colIndex] = true
                    } else {
                      this.isBackgroundHoverRow[colIndex] = false
                    }
                  })
                })
                .onTouch((event) => {
                  if (event.type === TouchType.Down) {
                    animateTo({
                      curve: SHARP_CUBIC_BEZIER,
                      duration: ANIMATION_DURATION_100
                    }, () => {
                      this.backgroundColorRow[colIndex] = $r('sys.color.ohos_id_color_click_effect')
                      this.isBackgroundHoverRow[colIndex] = true
                    })
                  } else if (event.type === TouchType.Up) {
                    animateTo({
                      curve: SHARP_CUBIC_BEZIER,
                      duration: ANIMATION_DURATION_100
                    }, () => {
                      this.isBackgroundHoverRow[colIndex] = false
                    })
                  }
                })
                .focusable(true)
                .stateStyles({
                  focused: {
                    .border({
                      radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                      width: FOCUS_BORDER_WIDTH,
                      color: $r('sys.color.ohos_id_color_focused_outline'),
                      style: BorderStyle.Solid
                    })
                    .padding({
                      left: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
                      right: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH
                    })
                  },
                  normal: {
                    .border({
                      radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                      width: 0 })
                    .padding({ left: TEXT_HOT_AREA_WIDTH, right: TEXT_HOT_AREA_WIDTH })
                  }
                })
            }
          })
          this.DownAndUpArrow()
        }.alignSelf(ItemAlign.Stretch)
      }.width(PERCENT_100)
      .padding({ right: $r('sys.float.ohos_id_max_padding_end') })
      .onAreaChange((_oldValue: Area, newValue: Area) => {
        this.filterColumnWidth = vp2px(parseInt(newValue.width.toString(), 0))
        if (this.twoLineModeItemNumRow.value === 0) {
          var curLineSum = this.calcMultiFilterRowItemNum()
          this.twoLineModeItemNumRow.value = curLineSum
          this.twoLineModeItemNumRecordRow.value = curLineSum
          if (curLineSum < this.filterRow.options.length - 1) {
            this.arrowShowStateRow.value = true
          } else {
            this.arrowShowStateRow.value = false
          }
        }
      })

    }.width(PERCENT_100)
    .alignItems(VerticalAlign.Top)
    .padding({ left: $r('sys.float.ohos_id_max_padding_start'), right: $r('sys.float.ohos_id_max_padding_end') })
  }
}


@Component
export struct Filter {
  @BuilderParam container: () => void
  @Prop multiFilters: Array<FilterParams> = []
  @Prop additionFilters: FilterParams = null
  onFilterChanged: (filterResults: Array<FilterResult>) => void = null
  @Prop filterType: FilterType = FilterType.LIST_FILTER
  private selectedFilters: Array<FilterResult> = null
  @State private colorArr: Array<ResourceArray> = null
  @State private fontWeightArr: Array<FontWeightArray> = null
  @State private backgroundColorArr: Array<ResourceArray> = null
  @State private isBackgroundHover: Array<BooleanArray> = null
  @State private floatArrowBgColor: Resource = null
  @State private isFloatArrowBgHover: boolean = false
  @State private isArrowIconDownArr: Array<ObservedBoolean> = null
  @State private additionColorArr: Array<Resource> = null
  @State private additionFontWeightArr: Array<FontWeight> = null
  @State private additionBackgroundColorArr: Array<Resource> = null
  @State private isAdditionBackgroundHover: Array<boolean> = null
  @State colorRefresh: boolean = false
  @State isFloatBarShow: boolean = false
  isFloatBarShowWithoutAnimation: boolean = false
  @State isFloatShowAllFilter: boolean = false
  isFloatShowAllFilterWithoutAnimation: boolean = false
  @State floatFilterPosition: number = 0
  @State floatFilterBarHeight: number = 0
  @State floatFilterBarPosition: number = 0
  filterDynamicHeight: number = 0
  @State twoLineModeItemNum: Array<ObservedNumber> = null
  @State twoLineModeItemNumRecord: Array<ObservedNumber> = null
  @State downArrowShowState: Array<ObservedBoolean> = null

  textColor(rowIndex: number, colIndex: number) {
    if (this.selectedFilters.length > rowIndex && this.selectedFilters[rowIndex].index === colIndex) {
      return $r('sys.color.ohos_id_color_text_primary_activated')
    }
    return $r('sys.color.ohos_id_color_text_primary')
  }

  aboutToAppear() {
    this.initParams()
  }

  private filterItemClick(rowIndex: number, colIndex: number) {
    let selectedFilterValue = this.multiFilters[rowIndex].options[colIndex]
    if (colIndex != this.selectedFilters[rowIndex].index) {
      this.colorArr[rowIndex][colIndex] = $r('sys.color.ohos_id_color_text_primary_activated')
      this.colorArr[rowIndex][this.selectedFilters[rowIndex].index] = $r('sys.color.ohos_id_color_text_primary')
      this.fontWeightArr[rowIndex][colIndex] = FontWeight.Medium
      this.fontWeightArr[rowIndex][this.selectedFilters[rowIndex].index] = FontWeight.Regular
      this.colorRefresh = !this.colorRefresh
      this.selectedFilters[rowIndex].value = selectedFilterValue
      this.selectedFilters[rowIndex].index = colIndex
      this.onFilterChanged && this.onFilterChanged(this.selectedFilters);
    }
  }

  private initParams() {
    if (!this.selectedFilters) {
      this.selectedFilters = []
      for (let filter of this.multiFilters) {
        var result: FilterResult = { name: filter.name, index: -1, value: null }
        if (filter.options.length > 0) {
          result.index = 0
          result.value = filter.options[0]
        }
        this.selectedFilters.push(result)
      }
      if (this.additionFilters && this.additionFilters.name) {
        var result: FilterResult = { name: this.additionFilters.name, index: -1, value: null }
        this.selectedFilters.push(result)
      }
    }
    if (!this.colorArr) {
      this.colorArr = []
      this.backgroundColorArr = []
      this.isBackgroundHover = []
      this.fontWeightArr = []
      this.isArrowIconDownArr = []
      this.floatArrowBgColor = $r('sys.color.ohos_id_color_hover')
      for (let filter of this.multiFilters) {
        var colorRow = new ResourceArray()
        var fontWeightRow = new FontWeightArray()
        var backgroundColorRow = new ResourceArray()
        var isBackgroundHoverRow = new BooleanArray()
        for (let index of filter.options.keys()) {
          if (index === 0) {
            colorRow.push($r('sys.color.ohos_id_color_text_primary_activated'))
            fontWeightRow.push(FontWeight.Medium)
          } else {
            colorRow.push($r('sys.color.ohos_id_color_text_primary'))
            fontWeightRow.push(FontWeight.Regular)
          }
          backgroundColorRow.push($r('sys.color.ohos_id_color_hover'))
        }
        this.colorArr.push(colorRow)
        this.fontWeightArr.push(fontWeightRow)
        this.backgroundColorArr.push(backgroundColorRow)
        this.isBackgroundHover.push(isBackgroundHoverRow)
        this.isArrowIconDownArr.push(new ObservedBoolean(true))
      }
    }
    if (this.additionFilters && this.additionFilters.options) {
      this.additionColorArr = []
      this.additionFontWeightArr = []
      this.additionBackgroundColorArr = []
      this.isAdditionBackgroundHover = []
      for (let i = 0; i < this.additionFilters.options.length; i++) {
        this.additionColorArr.push($r('sys.color.ohos_id_color_text_primary'))
        this.additionFontWeightArr.push(FontWeight.Regular)
        this.additionBackgroundColorArr.push($r('sys.color.ohos_id_color_hover'))
        this.isAdditionBackgroundHover.push(false)
      }
    }
    if (!this.twoLineModeItemNum) {
      this.twoLineModeItemNum = []
      this.twoLineModeItemNumRecord = []
      this.downArrowShowState = []
      for (let i = 0; i < this.multiFilters.length; i++) {
        this.twoLineModeItemNum.push(new ObservedNumber(0))
        this.twoLineModeItemNumRecord.push(new ObservedNumber(0))
        this.downArrowShowState.push(new ObservedBoolean(false))
      }
    }
  }

  @Builder ListFilter() {
    Column() {
      ForEach(this.multiFilters, (filter: FilterParams, rowIndex?: number) => {
        ListFilterRow({
          colorRow: this.colorArr[rowIndex],
          fontWeightRow: this.fontWeightArr[rowIndex],
          backgroundColorRow: this.backgroundColorArr[rowIndex],
          isBackgroundHoverRow: this.isBackgroundHover[rowIndex],
          filterRow: filter,
          onItemClick: (colIndex: number) => {
            this.filterItemClick(rowIndex, colIndex);
          }
        })
      })
    }.width(PERCENT_100)
    .align(Alignment.Start)
    .padding({ left: $r('sys.float.ohos_id_max_padding_start') })
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
        if (this.additionFilters != null) {
          this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING
        } else {
          this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + FILTER_TOP_PADDING
        }
        this.floatFilterPosition = -this.filterDynamicHeight
      }
    })
  }

  @Builder MultiLineFilter() {
    Column() {
      ForEach(this.multiFilters, (filterItem: FilterParams, rowIndex?: number) => {
        MultiFilterRow({
          colorRow: this.colorArr[rowIndex],
          fontWeightRow: this.fontWeightArr[rowIndex],
          backgroundColorRow: this.backgroundColorArr[rowIndex],
          isBackgroundHoverRow: this.isBackgroundHover[rowIndex],
          arrowShowStateRow: this.downArrowShowState[rowIndex],
          twoLineModeItemNumRow: this.twoLineModeItemNum[rowIndex],
          twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord[rowIndex],
          isArrowIconDown: this.isArrowIconDownArr[rowIndex],
          filterRow: filterItem,
          onItemClick: (colIndex: number) => {
            this.filterItemClick(rowIndex, colIndex);
          }
        })
      })
    }.width(PERCENT_100)
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      if (this.additionFilters != null) {
        this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING
      } else {
        this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + FILTER_TOP_PADDING
      }
      if (!this.isFloatBarShowWithoutAnimation && !this.isFloatShowAllFilterWithoutAnimation) {
        this.floatFilterPosition = -this.filterDynamicHeight
      }
    })
  }

  private additionItemClick(index: number) {
    let additionRowIndex = this.multiFilters.length
    if (this.selectedFilters[additionRowIndex].index != index) {
      if (this.selectedFilters[additionRowIndex].index === -1) {
        this.additionColorArr[index] = $r('sys.color.ohos_id_color_text_primary_activated')
        this.additionFontWeightArr[index] = FontWeight.Medium
        this.selectedFilters[additionRowIndex].value = this.additionFilters.options[index]
        this.selectedFilters[additionRowIndex].index = index
      } else {
        let lastIndex = this.selectedFilters[additionRowIndex].index
        this.additionColorArr[lastIndex] = $r('sys.color.ohos_id_color_text_primary')
        this.additionColorArr[index] = $r('sys.color.ohos_id_color_text_primary_activated')
        this.additionFontWeightArr[lastIndex] = FontWeight.Regular
        this.additionFontWeightArr[index] = FontWeight.Medium
        this.selectedFilters[additionRowIndex].value = this.additionFilters.options[index]
        this.selectedFilters[additionRowIndex].index = index
      }
    } else {
      this.additionColorArr[index] = $r('sys.color.ohos_id_color_text_primary')
      this.additionFontWeightArr[index] = FontWeight.Regular
      this.selectedFilters[additionRowIndex].value = null
      this.selectedFilters[additionRowIndex].index = -1
    }
    this.onFilterChanged && this.onFilterChanged(this.selectedFilters)
    this.colorRefresh = !this.colorRefresh
  }

  @Builder AdditionFilterList() {
    if (this.additionFilters && this.additionFilters.name && this.additionFilters.options && this.additionFilters.options.length != 0) {
      List() {
        ListItem() {
          Row() {
            Text(this.additionFilters.name.toString())
              .fontSize($r('sys.float.ohos_id_text_size_body3'))
              .fontColor($r('sys.color.ohos_id_color_text_secondary'))
              .margin({ left: TEXT_HOT_AREA_WIDTH, right: TEXT_HOT_AREA_WIDTH })
            Row()
              .width(SEPARATOR_WIDTH)
              .height(SEPARATOR_HEIGHT)
              .backgroundColor($r('sys.color.ohos_id_color_list_separator'))
          }
        }.height(PERCENT_100)

        ForEach(this.additionFilters.options, (option, index?: number) => {
          ListItem() {
            Text(option.toString())
              .fontSize($r('sys.float.ohos_id_text_size_body3'))
              .fontColor(this.additionColorArr[index])
              .fontWeight(this.additionFontWeightArr[index])
              .focusable(true)
          }
          .height(PERCENT_100)
          .backgroundColor(this.isAdditionBackgroundHover[index] ? this.additionBackgroundColorArr[index] : TRANS_COLOR)
          .onHover((isHover: boolean) => {
            animateTo({
              curve: FRICTION_CUBIC_BEZIER,
              duration: ANIMATION_DURATION_250
            }, () => {
              if (isHover) {
                this.additionBackgroundColorArr[index] = $r('sys.color.ohos_id_color_hover')
                this.isAdditionBackgroundHover[index] = true
              } else {
                this.isAdditionBackgroundHover[index] = false
              }
            })
          })
          .onTouch((event) => {
            if (event.type === TouchType.Down) {
              animateTo({
                curve: SHARP_CUBIC_BEZIER,
                duration: ANIMATION_DURATION_100
              }, () => {
                this.additionBackgroundColorArr[index] = $r('sys.color.ohos_id_color_click_effect')
                this.isAdditionBackgroundHover[index] = true
              })
            } else if (event.type === TouchType.Up) {
              animateTo({
                curve: SHARP_CUBIC_BEZIER,
                duration: ANIMATION_DURATION_100
              }, () => {
                this.isAdditionBackgroundHover[index] = false
              })
            }
          })
          .focusable(true)
          .stateStyles({
            focused: {
              .border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: FOCUS_BORDER_WIDTH,
                color: $r('sys.color.ohos_id_color_focused_outline'),
                style: BorderStyle.Solid
              })
              .padding({
                left: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH,
                right: TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH
              })
            },
            normal: {
              .border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: 0 })
              .padding({ left: TEXT_HOT_AREA_WIDTH, right: TEXT_HOT_AREA_WIDTH })
            }
          })
          .onClick(() => {
            this.additionItemClick(index)
          })
        })
      }
      .listDirection(Axis.Horizontal)
      .scrollBar(BarState.Off)
      .padding({ left: $r('sys.float.ohos_id_max_padding_start') })
      .margin({ left: -TEXT_HOT_AREA_WIDTH * 2 })
      .width(PERCENT_100)
      .height(LIST_ROW_HEIGHT)
    }

  }

  @Builder FilterHeader() {
    Column() {
      if (this.filterType === FilterType.LIST_FILTER) {
        this.ListFilter()
      } else {
        this.MultiLineFilter()
      }
      this.AdditionFilterList()
    }.padding({ top: FILTER_TOP_PADDING })
    .onVisibleAreaChange([0.0, 1.0], (_isVisible: boolean, currentRatio: number) => {
      if (currentRatio > 0) {
        this.isFloatShowAllFilter = false
        this.isFloatShowAllFilterWithoutAnimation = false
        this.isFloatBarShowWithoutAnimation = false
        animateTo({
          curve: INTER_POLATING_SPRING,
          onFinish: () => {
            if (!this.isFloatBarShowWithoutAnimation) {
              this.isFloatBarShow = false
            }
          }
        }, () => {
          this.floatFilterBarHeight = 0
        })
      } else {
        this.isFloatBarShow = true
        this.isFloatBarShowWithoutAnimation = true
        animateTo({
          curve: INTER_POLATING_SPRING
        }, () => {
          this.floatFilterBarHeight = LIST_ROW_HEIGHT + FILTER_TOP_PADDING
        })
      }
    })
  }

  @Builder FloatFilterHeader() {
    Column() {
      if (this.filterType === FilterType.LIST_FILTER) {
        this.ListFilter()
      } else {
        this.MultiLineFilter()
      }
      this.AdditionFilterList()
    }
    .padding({ top: FILTER_TOP_PADDING })
    .width(PERCENT_100)
    .clip(true)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .opacity(FLOAT_OPACITY)
    .backgroundBlurStyle(BlurStyle.Thin)
    .visibility(this.isFloatShowAllFilter ? Visibility.Visible : Visibility.Hidden)
    .position({ x: 0, y: this.floatFilterPosition })
    .zIndex(2)
  }

  @Builder FloatFilterBar() {
    Row() {
      Column() {
        Row() {
          ForEach(this.selectedFilters.slice(0, this.colorRefresh ? this.selectedFilters.length : this.selectedFilters.length), (selected, index?: number) => {
            if (index != 0 && selected.value != null) {
              Text('/')
                .fontColor($r('sys.color.ohos_id_color_text_primary'))
                .fontSize($r('sys.float.ohos_id_text_size_body3'))
            }
            Text(selected.value)
              .fontColor($r('sys.color.ohos_id_color_text_primary'))
              .fontSize($r('sys.float.ohos_id_text_size_body3'))
          })
        }.height(PERCENT_100)
        .alignItems(VerticalAlign.Center)
      }
      .alignItems(HorizontalAlign.Center)
      .width(PERCENT_100)
      .height(LIST_ROW_HEIGHT)

      Row() {
        Image($r('sys.media.ohos_ic_public_arrow_down'))
          .width(ARROW_IMG_SIZE)
          .height(ARROW_IMG_SIZE)
          .fillColor($r('sys.color.ohos_id_color_tertiary'))
          .focusable(true)
      }
      .height(LIST_ROW_HEIGHT)
      .margin({ left: -ARROW_IMG_SIZE })
      .backgroundColor(this.isFloatArrowBgHover ? this.floatArrowBgColor : TRANS_COLOR)
      .focusable(true)
      .stateStyles({
        focused: {
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: FOCUS_BORDER_WIDTH,
            color: $r('sys.color.ohos_id_color_focused_outline'),
            style: BorderStyle.Solid
          })
          .width(ARROW_IMG_SIZE + FOCUS_BORDER_WIDTH * 2)
          .offset({ x: -FOCUS_BORDER_WIDTH })
        },
        normal: {
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: 0 })
          .width(ARROW_IMG_SIZE)
          .offset({ x: 0 })
        }
      })
      .onHover((isHover: boolean) => {
        if (isHover) {
          animateTo({
            curve: FRICTION_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_250
          }, () => {
            this.floatArrowBgColor = $r('sys.color.ohos_id_color_hover')
            this.isFloatArrowBgHover = true
          })
        } else {
          animateTo({
            curve: FRICTION_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_250
          }, () => {
            this.isFloatArrowBgHover = false
          })
        }
      })
      .onTouch((event) => {
        if (event.type === TouchType.Down) {
          animateTo({
            curve: SHARP_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_100
          }, () => {
            this.floatArrowBgColor = $r('sys.color.ohos_id_color_click_effect')
            this.isFloatArrowBgHover = true
          })
        } else if (event.type === TouchType.Up) {
          animateTo({
            curve: SHARP_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_100
          }, () => {
            this.isFloatArrowBgHover = false
          })
        }
      })
      .onClick(() => {
        animateTo({
          duration: BAR_ANIMATION_DURATION,
          curve: SHARP_CUBIC_BEZIER
        }, () => {
          this.isFloatBarShow = false
          this.isFloatBarShowWithoutAnimation = false
        })
        this.isFloatShowAllFilter = true
        this.isFloatShowAllFilterWithoutAnimation = true
        animateTo({
          curve: INTER_POLATING_SPRING
        }, () => {
          this.floatFilterPosition = 0
          this.floatFilterBarPosition = this.filterDynamicHeight
        })
      })
    }
    .width(PERCENT_100)
    .padding({ right: $r('sys.float.ohos_id_max_padding_end') })
    .height(this.floatFilterBarHeight)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .opacity(FLOAT_OPACITY)
    .clip(true)
    .backgroundBlurStyle(BlurStyle.Thin)
    .visibility(this.isFloatBarShow ? Visibility.Visible : Visibility.Hidden)
    .alignItems(VerticalAlign.Bottom)
    .position({ x: 0, y: this.floatFilterBarPosition })
    .zIndex(1)
  }

  private listScroller: Scroller = new Scroller()

  build() {
    Stack({ alignContent: Alignment.Top }) {
      this.FloatFilterBar();
      this.FloatFilterHeader();
      Column() {
        List({ initialIndex: 0, scroller: this.listScroller }) {
          ListItem() {
            this.FilterHeader()
          }.focusable(true)
          .onFocus(() => {
            this.listScroller.scrollToIndex(0, true)
          })

          ListItem() {
            this.container()
          }.focusable(true)
          .onFocus(() => {
            this.listScroller.scrollToIndex(1, true)
          })
        }
        .listDirection(Axis.Vertical)
        .width(PERCENT_100)
        .height(PERCENT_100)
        .edgeEffect(EdgeEffect.Spring)
        .onScroll((_scrollOffset: number, scrollState: ScrollState) => {
          if (this.isFloatShowAllFilterWithoutAnimation && scrollState == ScrollState.Scroll) {
            this.isFloatBarShowWithoutAnimation = true
            this.isFloatShowAllFilterWithoutAnimation = false
            animateTo({
              duration: BAR_ANIMATION_DURATION,
              curve: SHARP_CUBIC_BEZIER
            }, () => {
              this.isFloatBarShow = true
            })

            animateTo({
              curve: INTER_POLATING_SPRING,
              onFinish: () => {
                if (!this.isFloatShowAllFilterWithoutAnimation) {
                  this.isFloatShowAllFilter = false
                }
              }
            }, () => {
              this.floatFilterPosition = -this.filterDynamicHeight
              this.floatFilterBarPosition = 0
            })
          }
        })
      }.zIndex(0)
    }.clip(true)
  }
}