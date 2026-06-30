/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { autoUILpx, autoUILpxDim, autoUILpxN, CommonConstants } from "../utils/BreakPointSystem";
import { NavigationManager } from "../utils/NavigationManager";
import { LengthMetrics } from "@kit.ArkUI";

enum PickerType {
  None = '',
  TimePicker = 'TimePicker',
  CalendarPicker = 'CalendarPicker',
  TextPicker = 'TextPicker',
  DatePicker = 'DatePicker',
  UIPickerComponent = 'UIPickerComponent'
}

enum CalendarTestType {
  None = '',
  TextStyle = 'TextStyle',
  EdgeAlign = 'edgeAlign',
  PaddingLength = 'padding(Length)',
  PaddingPadding = 'padding(Padding)',
  PaddingLocalizedPadding = 'padding(LocalizedPadding)'
}

enum UIPickerTestType {
  None = '',
  ItemHeight = 'itemHeight',
  IndicatorDivider = 'indicator(divider)',
  IndicatorBorderRadiusLengthMetrics = 'indicator(borderRadius_lengthMetrics)',
  IndicatorBorderRadiusBorderRadius = 'indicator(borderRadius_BorderRadius)',
  IndicatorBorderRadiusLocalizedBorderRadiuses = 'indicator(borderRadius_LocalizedBorderRadiuses)'
}

enum TextPickerTestType {
  None = '',
  TextStyle = 'TextStyle',
  DefaultPickerItemHeight = 'defaultPickerItemHeight',
  GradientHeight = 'gradientHeight',
  ColumnWidths = 'columnWidths',
  DefaultTextStyle = 'defaultTextStyle',
  SelectedBackgroundStyleLengthMetrics = 'selectedBackgroundStyle(lengthMetrics)',
  SelectedBackgroundStyleBorderRadius = 'selectedBackgroundStyle(BorderRadius)',
  SelectedBackgroundStyleLocalizedBorderRadiuses = 'selectedBackgroundStyle(LocalizedBorderRadiuses)',
  Divider = 'divider'
}

const TEXT_PICKER_RANGE: string[] = [
  '测试文本001', '测试文本002', '测试文本003', '测试文本004', '测试文本005',
  '测试文本006', '测试文本007', '测试文本008', '测试文本009', '测试文本010',
  '测试文本011', '测试文本012', '测试文本013', '测试文本014', '测试文本015',
  '测试文本016', '测试文本017', '测试文本018', '测试文本019', '测试文本020'
]

const PRIMARY_BUTTON_COLOR = '#B3D7FF'
const PRIMARY_BUTTON_TEXT_COLOR = '#1565C0'
const PRIMARY_BUTTON_SELECTED_COLOR = '#0A2472'
const SECONDARY_BUTTON_COLOR = '#FFD699'
const SECONDARY_BUTTON_TEXT_COLOR = '#E65100'
const SECONDARY_BUTTON_SELECTED_COLOR = '#C43C00'
const BUTTON_SELECTED_BORDER_COLOR = '#FFEB3B'

@Builder
export function OnePageBuilder() {
  OnePage();
}

@Entry
@Component
struct OnePage {
  @StorageProp('currentBreakPoint') currentBreakPoint: string = CommonConstants.MD;
  @State message: string = '测试字体改变';
  @State selectedPicker: PickerType = PickerType.None;
  @State calendarTestType: CalendarTestType = CalendarTestType.None;
  @State uiPickerTestType: UIPickerTestType = UIPickerTestType.None;
  @State textPickerTestType: TextPickerTestType = TextPickerTestType.None;
  @State uiPickerSelectedIndex: number = 0;

  getSelectedPickerLabel(): string {
    if (this.selectedPicker === PickerType.None) {
      return '未选择'
    }
    return this.selectedPicker
  }

  getSelectedSecondaryTestLabel(): string {
    if (this.selectedPicker === PickerType.CalendarPicker) {
      if (this.calendarTestType === CalendarTestType.None) {
        return '未选择'
      }
      return this.calendarTestType
    }
    if (this.selectedPicker === PickerType.UIPickerComponent) {
      if (this.uiPickerTestType === UIPickerTestType.None) {
        return '未选择'
      }
      return this.uiPickerTestType
    }
    if (this.selectedPicker === PickerType.TextPicker) {
      if (this.textPickerTestType === TextPickerTestType.None) {
        return '未选择'
      }
      return this.textPickerTestType
    }
    return '无'
  }

  resetSecondaryTestType(): void {
    this.calendarTestType = CalendarTestType.None
    this.uiPickerTestType = UIPickerTestType.None
    this.textPickerTestType = TextPickerTestType.None
  }

  @Builder
  primaryOptionButton(label: string, picker: PickerType) {
    Button(label)
      .backgroundColor(this.selectedPicker === picker ?
        PRIMARY_BUTTON_SELECTED_COLOR : PRIMARY_BUTTON_COLOR)
      .fontColor(this.selectedPicker === picker ? Color.White : PRIMARY_BUTTON_TEXT_COLOR)
      .borderWidth(this.selectedPicker === picker ? 3 : 0)
      .borderColor(BUTTON_SELECTED_BORDER_COLOR)
      .onClick(() => {
        this.selectedPicker = picker
        this.resetSecondaryTestType()
      })
  }

  @Builder
  secondaryCalendarOptionButton(label: string, testType: CalendarTestType) {
    Button(label)
      .backgroundColor(this.calendarTestType === testType ?
        SECONDARY_BUTTON_SELECTED_COLOR : SECONDARY_BUTTON_COLOR)
      .fontColor(this.calendarTestType === testType ? Color.White : SECONDARY_BUTTON_TEXT_COLOR)
      .borderWidth(this.calendarTestType === testType ? 3 : 0)
      .borderColor(BUTTON_SELECTED_BORDER_COLOR)
      .onClick(() => {
        this.calendarTestType = testType
      })
  }

  @Builder
  secondaryUIPickerOptionButton(label: string, testType: UIPickerTestType) {
    Button(label)
      .backgroundColor(this.uiPickerTestType === testType ?
        SECONDARY_BUTTON_SELECTED_COLOR : SECONDARY_BUTTON_COLOR)
      .fontColor(this.uiPickerTestType === testType ? Color.White : SECONDARY_BUTTON_TEXT_COLOR)
      .borderWidth(this.uiPickerTestType === testType ? 3 : 0)
      .borderColor(BUTTON_SELECTED_BORDER_COLOR)
      .onClick(() => {
        this.uiPickerTestType = testType
      })
  }

  @Builder
  secondaryTextPickerOptionButton(label: string, testType: TextPickerTestType) {
    Button(label)
      .backgroundColor(this.textPickerTestType === testType ?
        SECONDARY_BUTTON_SELECTED_COLOR : SECONDARY_BUTTON_COLOR)
      .fontColor(this.textPickerTestType === testType ? Color.White : SECONDARY_BUTTON_TEXT_COLOR)
      .borderWidth(this.textPickerTestType === testType ? 3 : 0)
      .borderColor(BUTTON_SELECTED_BORDER_COLOR)
      .onClick(() => {
        this.textPickerTestType = testType
      })
  }

  @Builder
  uiPickerItems() {
    ForEach(TEXT_PICKER_RANGE, (item: string) => {
      Text(item)
        .width('100%')
        .textAlign(TextAlign.Center)
    }, (item: string) => item)
  }

  @Builder
  calendarTextStyleTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(40, 25)')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .textStyle({ font: { size: autoUILpx(this.currentBreakPoint, 40, 25) } })
      }

      Column({ space: 5 }) {
        Text('40lpx')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .textStyle({ font: { size: '40lpx' } })
      }

      Column({ space: 5 }) {
        Text('25lpx')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .textStyle({ font: { size: '25lpx' } })
      }
    }
    .width('100%')
  }

  @Builder
  calendarEdgeAlignTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(200, -200)')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .edgeAlign(CalendarAlign.CENTER,
            { dx: autoUILpx(this.currentBreakPoint, 200, -200), dy: autoUILpx(this.currentBreakPoint, 200, -200) })
      }

      Column({ space: 5 }) {
        Text('200lpx')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .edgeAlign(CalendarAlign.CENTER, {dx: '200lpx', dy: '200lpx'})
      }

      Column({ space: 5 }) {
        Text('-200lpx')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .edgeAlign(CalendarAlign.CENTER, {dx: '-200lpx', dy: '-200lpx'})
      }
    }
    .width('100%')
  }

  @Builder
  calendarPaddingLengthTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(20, 5)')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .padding(autoUILpx(this.currentBreakPoint, 20, 5))
      }

      Column({ space: 5 }) {
        Text('20lpx')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .padding('20lpx')
      }

      Column({ space: 5 }) {
        Text('5lpx')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .padding('5lpx')
      }
    }
    .width('100%')
  }

  @Builder
  calendarPaddingPaddingTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(20, 5)')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .padding({
            top: autoUILpx(this.currentBreakPoint, 20, 5),
            right: autoUILpx(this.currentBreakPoint, 20, 5),
            bottom: autoUILpx(this.currentBreakPoint, 20, 5),
            left: autoUILpx(this.currentBreakPoint, 20, 5)
          })
      }

      Column({ space: 5 }) {
        Text('20lpx')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .padding({top: '20lpx', right: '20lpx', bottom: '20lpx', left: '20lpx'})
      }

      Column({ space: 5 }) {
        Text('5lpx')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .padding({top: '5lpx', right: '5lpx', bottom: '5lpx', left: '5lpx'})
      }
    }
    .width('100%')
  }

  @Builder
  calendarPaddingLocalizedPaddingTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(20, 5)')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .padding({
            top: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5)),
            end: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5)),
            bottom: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5)),
            start: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5))
          })
      }

      Column({ space: 5 }) {
        Text('20lpx')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .padding({
            top: LengthMetrics.lpx(20),
            end: LengthMetrics.lpx(20),
            bottom: LengthMetrics.lpx(20),
            start: LengthMetrics.lpx(20)
          })
      }

      Column({ space: 5 }) {
        Text('5lpx')
          .fontColor(Color.Yellow)
        CalendarPicker()
          .padding({
            top: LengthMetrics.lpx(5),
            end: LengthMetrics.lpx(5),
            bottom: LengthMetrics.lpx(5),
            start: LengthMetrics.lpx(5)
          })
      }
    }
    .width('100%')
  }

  @Builder
  uiPickerItemHeightTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(55, 40)')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .itemHeight(LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 55, 40)))
        .width('100%')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('55lpx')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .itemHeight(LengthMetrics.lpx(55))
        .width('100%')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('40lpx')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .itemHeight(LengthMetrics.lpx(40))
        .width('100%')
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  uiPickerIndicatorDividerTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(20, 5)')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER,
          strokeWidth: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5)),
          startMargin: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5)),
          endMargin: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5)),
          dividerColor: '#FF5722'
        })
        .height(240)
        .width('100%')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('20lpx')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER,
          strokeWidth: LengthMetrics.lpx(20),
          startMargin: LengthMetrics.lpx(20),
          endMargin: LengthMetrics.lpx(20),
          dividerColor: '#FF5722'
        })
        .height(240)
        .width('100%')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('5lpx')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER,
          strokeWidth: LengthMetrics.lpx(5),
          startMargin: LengthMetrics.lpx(5),
          endMargin: LengthMetrics.lpx(5),
          dividerColor: '#FF5722'
        })
        .height(240)
        .width('100%')
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  uiPickerIndicatorBorderRadiusLengthMetricsTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(20, 5)')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.BACKGROUND,
          backgroundColor: '#33007DFF',
          borderRadius: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5))
        })
        .height(240)
        .width('100%')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('20lpx')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.BACKGROUND,
          backgroundColor: '#33007DFF',
          borderRadius: LengthMetrics.lpx(20)
        })
        .height(240)
        .width('100%')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('5lpx')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.BACKGROUND,
          backgroundColor: '#33007DFF',
          borderRadius: LengthMetrics.lpx(5)
        })
        .height(240)
        .width('100%')
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  uiPickerIndicatorBorderRadiusBorderRadiusTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(20, 5)')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.BACKGROUND,
          backgroundColor: '#33007DFF',
          borderRadius: {
            topLeft: autoUILpx(this.currentBreakPoint, 20, 5),
            topRight: autoUILpx(this.currentBreakPoint, 20, 5),
            bottomLeft: autoUILpx(this.currentBreakPoint, 20, 5),
            bottomRight: autoUILpx(this.currentBreakPoint, 20, 5)
          }
        })
        .height(240)
        .width('100%')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('20lpx')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.BACKGROUND,
          backgroundColor: '#33007DFF',
          borderRadius: {
            topLeft: '20lpx',
            topRight: '20lpx',
            bottomLeft: '20lpx',
            bottomRight: '20lpx'
          }
        })
        .height(240)
        .width('100%')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('5lpx')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.BACKGROUND,
          backgroundColor: '#33007DFF',
          borderRadius: {
            topLeft: '5lpx',
            topRight: '5lpx',
            bottomLeft: '5lpx',
            bottomRight: '5lpx'
          }
        })
        .height(240)
        .width('100%')
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  uiPickerIndicatorBorderRadiusLocalizedBorderRadiusesTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(20, 5)')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.BACKGROUND,
          backgroundColor: '#33007DFF',
          borderRadius: {
            topStart: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5)),
            topEnd: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5)),
            bottomStart: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5)),
            bottomEnd: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 20, 5))
          }
        })
        .height(240)
        .width('100%')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('20lpx')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.BACKGROUND,
          backgroundColor: '#33007DFF',
          borderRadius: {
            topStart: LengthMetrics.lpx(20),
            topEnd: LengthMetrics.lpx(20),
            bottomStart: LengthMetrics.lpx(20),
            bottomEnd: LengthMetrics.lpx(20)
          }
        })
        .height(240)
        .width('100%')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('5lpx')
          .fontColor(Color.Yellow)
        UIPickerComponent({ selectedIndex: this.uiPickerSelectedIndex }) {
          this.uiPickerItems()
        }
        .selectionIndicator({
          type: PickerIndicatorType.BACKGROUND,
          backgroundColor: '#33007DFF',
          borderRadius: {
            topStart: LengthMetrics.lpx(5),
            topEnd: LengthMetrics.lpx(5),
            bottomStart: LengthMetrics.lpx(5),
            bottomEnd: LengthMetrics.lpx(5)
          }
        })
        .height(240)
        .width('100%')
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  textPickerTextStyleTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(40, 25)')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedTextStyle({ font: { size: autoUILpx(this.currentBreakPoint, 40, 25) } })
          .disappearTextStyle({ font: { size: autoUILpx(this.currentBreakPoint, 40, 25) } })
          .textStyle({ font: { size: autoUILpx(this.currentBreakPoint, 40, 25) } })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('40lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedTextStyle({ font: { size: '40lpx' } })
          .disappearTextStyle({ font: { size: '40lpx' } })
          .textStyle({ font: { size: '40lpx' } })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('25lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedTextStyle({ font: { size: '25lpx' } })
          .disappearTextStyle({ font: { size: '25lpx' } })
          .textStyle({ font: { size: '25lpx' } })
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  textPickerDefaultPickerItemHeightTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(50, 35)')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .defaultPickerItemHeight(autoUILpx(this.currentBreakPoint, 50, 35))
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('50lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .defaultPickerItemHeight('50lpx')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('35lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .defaultPickerItemHeight('35lpx')
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  textPickerGradientHeightTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(20, 100)')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .gradientHeight(autoUILpxDim(this.currentBreakPoint, 20, 100))
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('20lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .gradientHeight('20lpx')
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('100lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .gradientHeight('100lpx')
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  textPickerColumnWidthsTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(205, 75)')
          .fontColor(Color.Yellow)
        TextPicker({
          range: TEXT_PICKER_RANGE,
          columnWidths: [
            LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 205, 75))
          ]
        })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('205lpx')
          .fontColor(Color.Yellow)
        TextPicker({
          range: TEXT_PICKER_RANGE,
          columnWidths: [
            LengthMetrics.lpx(205)
          ]
        })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('75lpx')
          .fontColor(Color.Yellow)
        TextPicker({
          range: TEXT_PICKER_RANGE,
          columnWidths: [
            LengthMetrics.lpx(75)
          ]
        })
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  textPickerDefaultTextStyleTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('min(35,15),max(40,20)')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .disableTextStyleAnimation(true)
          .defaultTextStyle({
            minFontSize: autoUILpx(this.currentBreakPoint, 35, 15),
            maxFontSize: autoUILpx(this.currentBreakPoint, 40, 20)
          })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('min: 35lpx, max: 40lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .disableTextStyleAnimation(true)
          .defaultTextStyle({
            minFontSize: '35lpx',
            maxFontSize: '40lpx'
          })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('min: 15lpx, max: 20lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .disableTextStyleAnimation(true)
          .defaultTextStyle({
            minFontSize: '15lpx',
            maxFontSize: '20lpx'
          })
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  textPickerSelectedBackgroundStyleLengthMetricsTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(24, 5)')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedBackgroundStyle({
            color: '#33007DFF',
            borderRadius: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 24, 5))
          })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('24lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedBackgroundStyle({
            color: '#33007DFF',
            borderRadius: LengthMetrics.lpx(24)
          })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('5lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedBackgroundStyle({
            color: '#33007DFF',
            borderRadius: LengthMetrics.lpx(5)
          })
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  textPickerSelectedBackgroundStyleBorderRadiusTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(24, 5)')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedBackgroundStyle({
            color: '#33007DFF',
            borderRadius: {
              topLeft: autoUILpx(this.currentBreakPoint, 24, 5),
              topRight: autoUILpx(this.currentBreakPoint, 24, 5),
              bottomLeft: autoUILpx(this.currentBreakPoint, 24, 5),
              bottomRight: autoUILpx(this.currentBreakPoint, 24, 5)
            }
          })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('24lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedBackgroundStyle({
            color: '#33007DFF',
            borderRadius: {
              topLeft: '24lpx',
              topRight: '24lpx',
              bottomLeft: '24lpx',
              bottomRight: '24lpx'
            }
          })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('5lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedBackgroundStyle({
            color: '#33007DFF',
            borderRadius: {
              topLeft: '5lpx',
              topRight: '5lpx',
              bottomLeft: '5lpx',
              bottomRight: '5lpx'
            }
          })
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  textPickerSelectedBackgroundStyleLocalizedBorderRadiusesTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(24, 5)')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedBackgroundStyle({
            color: '#33007DFF',
            borderRadius: {
              topStart: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 24, 5)),
              topEnd: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 24, 5)),
              bottomStart: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 24, 5)),
              bottomEnd: LengthMetrics.lpx(autoUILpxN(this.currentBreakPoint, 24, 5))
            }
          })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('24lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedBackgroundStyle({
            color: '#33007DFF',
            borderRadius: {
              topStart: LengthMetrics.lpx(24),
              topEnd: LengthMetrics.lpx(24),
              bottomStart: LengthMetrics.lpx(24),
              bottomEnd: LengthMetrics.lpx(24)
            }
          })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('5lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .selectedBackgroundStyle({
            color: '#33007DFF',
            borderRadius: {
              topStart: LengthMetrics.lpx(5),
              topEnd: LengthMetrics.lpx(5),
              bottomStart: LengthMetrics.lpx(5),
              bottomEnd: LengthMetrics.lpx(5)
            }
          })
      }
      .width('33%')
    }
    .width('100%')
  }

  @Builder
  textPickerDividerTest() {
    Row({ space: 5 }) {
      Column({ space: 5 }) {
        Text('autoUILpx(20, 5)')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .divider({
            strokeWidth: autoUILpxDim(this.currentBreakPoint, 20, 5),
            startMargin: autoUILpxDim(this.currentBreakPoint, 20, 5),
            endMargin: autoUILpxDim(this.currentBreakPoint, 20, 5),
            color: '#FF5722'
          })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('20lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .divider({
            strokeWidth: '20lpx',
            startMargin: '20lpx',
            endMargin: '20lpx',
            color: '#FF5722'
          })
      }
      .width('33%')

      Column({ space: 5 }) {
        Text('5lpx')
          .fontColor(Color.Yellow)
        TextPicker({ range: TEXT_PICKER_RANGE })
          .width('100%')
          .divider({
            strokeWidth: '5lpx',
            startMargin: '5lpx',
            endMargin: '5lpx',
            color: '#FF5722'
          })
      }
      .width('33%')
    }
    .width('100%')
  }

  build() {
    NavDestination() {
      Column() {
        Text(this.message)
          .fontColor('333333')
          .fontSize(autoUILpx(this.currentBreakPoint, 40, 25))

        Scroll() {
          Row({ space: 8 }) {
            this.primaryOptionButton('TimePicker', PickerType.TimePicker)
            this.primaryOptionButton('DatePicker', PickerType.DatePicker)
            this.primaryOptionButton('CalendarPicker', PickerType.CalendarPicker)
            this.primaryOptionButton('TextPicker', PickerType.TextPicker)
            this.primaryOptionButton('UIPickerComponent', PickerType.UIPickerComponent)
          }
        }
        .scrollable(ScrollDirection.Horizontal)
        .scrollBar(BarState.Auto)
        .width('100%')
        .padding({ left: 12, right: 12, top: 8, bottom: 8 })

        if (this.selectedPicker === PickerType.CalendarPicker) {
          Scroll() {
            Row({ space: 8 }) {
              this.secondaryCalendarOptionButton('TextStyle', CalendarTestType.TextStyle)
              this.secondaryCalendarOptionButton('edgeAlign', CalendarTestType.EdgeAlign)
              this.secondaryCalendarOptionButton('padding(Length)', CalendarTestType.PaddingLength)
              this.secondaryCalendarOptionButton('padding(Padding)', CalendarTestType.PaddingPadding)
              this.secondaryCalendarOptionButton('padding(LocalizedPadding)', CalendarTestType.PaddingLocalizedPadding)
            }
          }
          .scrollable(ScrollDirection.Horizontal)
          .scrollBar(BarState.Auto)
          .width('100%')
          .padding({ left: 12, right: 12, bottom: 8 })
        }

        if (this.selectedPicker === PickerType.UIPickerComponent) {
          Scroll() {
            Row({ space: 8 }) {
              this.secondaryUIPickerOptionButton('itemHeight', UIPickerTestType.ItemHeight)
              this.secondaryUIPickerOptionButton('indicator(divider)', UIPickerTestType.IndicatorDivider)
              this.secondaryUIPickerOptionButton('indicator(borderRadius_lengthMetrics)',
                UIPickerTestType.IndicatorBorderRadiusLengthMetrics)
              this.secondaryUIPickerOptionButton('indicator(borderRadius_BorderRadius)',
                UIPickerTestType.IndicatorBorderRadiusBorderRadius)
              this.secondaryUIPickerOptionButton('indicator(borderRadius_LocalizedBorderRadiuses)',
                UIPickerTestType.IndicatorBorderRadiusLocalizedBorderRadiuses)
            }
          }
          .scrollable(ScrollDirection.Horizontal)
          .scrollBar(BarState.Auto)
          .width('100%')
          .padding({ left: 12, right: 12, bottom: 8 })
        }

        if (this.selectedPicker === PickerType.TextPicker) {
          Scroll() {
            Row({ space: 8 }) {
              this.secondaryTextPickerOptionButton('TextStyle', TextPickerTestType.TextStyle)
              this.secondaryTextPickerOptionButton('defaultPickerItemHeight',
                TextPickerTestType.DefaultPickerItemHeight)
              this.secondaryTextPickerOptionButton('gradientHeight', TextPickerTestType.GradientHeight)
              this.secondaryTextPickerOptionButton('columnWidths', TextPickerTestType.ColumnWidths)
              this.secondaryTextPickerOptionButton('defaultTextStyle', TextPickerTestType.DefaultTextStyle)
              this.secondaryTextPickerOptionButton('selectedBackgroundStyle(lengthMetrics)',
                TextPickerTestType.SelectedBackgroundStyleLengthMetrics)
              this.secondaryTextPickerOptionButton('selectedBackgroundStyle(BorderRadius)',
                TextPickerTestType.SelectedBackgroundStyleBorderRadius)
              this.secondaryTextPickerOptionButton('selectedBackgroundStyle(LocalizedBorderRadiuses)',
                TextPickerTestType.SelectedBackgroundStyleLocalizedBorderRadiuses)
              this.secondaryTextPickerOptionButton('divider', TextPickerTestType.Divider)
            }
          }
          .scrollable(ScrollDirection.Horizontal)
          .scrollBar(BarState.Auto)
          .width('100%')
          .padding({ left: 12, right: 12, bottom: 8 })
        }

        Row({ space: 16 }) {
          Text(`一级选项：${this.getSelectedPickerLabel()}`)
            .fontColor(PRIMARY_BUTTON_SELECTED_COLOR)
            .fontSize(autoUILpx(this.currentBreakPoint, 28, 18))
            .fontWeight(FontWeight.Medium)
          Text(`二级选项：${this.getSelectedSecondaryTestLabel()}`)
            .fontColor(SECONDARY_BUTTON_SELECTED_COLOR)
            .fontSize(autoUILpx(this.currentBreakPoint, 28, 18))
            .fontWeight(FontWeight.Medium)
        }
        .width('100%')
        .padding({ left: 12, right: 12, bottom: 8 })

        Scroll() {
          Column() {
            if (this.selectedPicker === PickerType.TimePicker) {
              Row({space: 5}) {
                Column({ space: 5 }) {
                  Text('autoUILpx(40, 25)')
                    .fontColor(Color.Yellow)
                  TimePicker()
                    .width('33%')
                    .selectedTextStyle({ font: { size: autoUILpx(this.currentBreakPoint, 40, 25) } })
                    .disappearTextStyle({ font: { size: autoUILpx(this.currentBreakPoint, 40, 25) } })
                    .textStyle({ font: { size: autoUILpx(this.currentBreakPoint, 40, 25) } })
                }

                Column({ space: 5 }) {
                  Text('40lpx')
                    .fontColor(Color.Yellow)
                  TimePicker()
                    .width('33%')
                    .selectedTextStyle({ font: { size: '40lpx' } })
                    .disappearTextStyle({ font: { size: '40lpx' } })
                    .textStyle({ font: { size:'40lpx' } })
                }

                Column({ space: 5 }) {
                  Text('25lpx')
                    .fontColor(Color.Yellow)
                  TimePicker()
                    .width('33%')
                    .selectedTextStyle({ font: { size: '25lpx' } })
                    .disappearTextStyle({ font: { size: '25lpx' } })
                    .textStyle({ font: { size: '25lpx' } })
                }
              }
            }

            if (this.selectedPicker === PickerType.CalendarPicker &&
              this.calendarTestType === CalendarTestType.TextStyle) {
              this.calendarTextStyleTest()
            }

            if (this.selectedPicker === PickerType.CalendarPicker &&
              this.calendarTestType === CalendarTestType.EdgeAlign) {
              this.calendarEdgeAlignTest()
            }

            if (this.selectedPicker === PickerType.CalendarPicker &&
              this.calendarTestType === CalendarTestType.PaddingLength) {
              this.calendarPaddingLengthTest()
            }

            if (this.selectedPicker === PickerType.CalendarPicker &&
              this.calendarTestType === CalendarTestType.PaddingPadding) {
              this.calendarPaddingPaddingTest()
            }

            if (this.selectedPicker === PickerType.CalendarPicker &&
              this.calendarTestType === CalendarTestType.PaddingLocalizedPadding) {
              this.calendarPaddingLocalizedPaddingTest()
            }

            if (this.selectedPicker === PickerType.UIPickerComponent &&
              this.uiPickerTestType === UIPickerTestType.ItemHeight) {
              this.uiPickerItemHeightTest()
            }

            if (this.selectedPicker === PickerType.UIPickerComponent &&
              this.uiPickerTestType === UIPickerTestType.IndicatorDivider) {
              this.uiPickerIndicatorDividerTest()
            }

            if (this.selectedPicker === PickerType.UIPickerComponent &&
              this.uiPickerTestType === UIPickerTestType.IndicatorBorderRadiusLengthMetrics) {
              this.uiPickerIndicatorBorderRadiusLengthMetricsTest()
            }

            if (this.selectedPicker === PickerType.UIPickerComponent &&
              this.uiPickerTestType === UIPickerTestType.IndicatorBorderRadiusBorderRadius) {
              this.uiPickerIndicatorBorderRadiusBorderRadiusTest()
            }

            if (this.selectedPicker === PickerType.UIPickerComponent &&
              this.uiPickerTestType === UIPickerTestType.IndicatorBorderRadiusLocalizedBorderRadiuses) {
              this.uiPickerIndicatorBorderRadiusLocalizedBorderRadiusesTest()
            }

            if (this.selectedPicker === PickerType.TextPicker &&
              this.textPickerTestType === TextPickerTestType.TextStyle) {
              this.textPickerTextStyleTest()
            }

            if (this.selectedPicker === PickerType.TextPicker &&
              this.textPickerTestType === TextPickerTestType.DefaultPickerItemHeight) {
              this.textPickerDefaultPickerItemHeightTest()
            }

            if (this.selectedPicker === PickerType.TextPicker &&
              this.textPickerTestType === TextPickerTestType.GradientHeight) {
              this.textPickerGradientHeightTest()
            }

            if (this.selectedPicker === PickerType.TextPicker &&
              this.textPickerTestType === TextPickerTestType.ColumnWidths) {
              this.textPickerColumnWidthsTest()
            }

            if (this.selectedPicker === PickerType.TextPicker &&
              this.textPickerTestType === TextPickerTestType.DefaultTextStyle) {
              this.textPickerDefaultTextStyleTest()
            }

            if (this.selectedPicker === PickerType.TextPicker &&
              this.textPickerTestType === TextPickerTestType.SelectedBackgroundStyleLengthMetrics) {
              this.textPickerSelectedBackgroundStyleLengthMetricsTest()
            }

            if (this.selectedPicker === PickerType.TextPicker &&
              this.textPickerTestType === TextPickerTestType.SelectedBackgroundStyleBorderRadius) {
              this.textPickerSelectedBackgroundStyleBorderRadiusTest()
            }

            if (this.selectedPicker === PickerType.TextPicker &&
              this.textPickerTestType === TextPickerTestType.SelectedBackgroundStyleLocalizedBorderRadiuses) {
              this.textPickerSelectedBackgroundStyleLocalizedBorderRadiusesTest()
            }

            if (this.selectedPicker === PickerType.TextPicker &&
              this.textPickerTestType === TextPickerTestType.Divider) {
              this.textPickerDividerTest()
            }

            if (this.selectedPicker === PickerType.DatePicker) {
              Row({ space: 5 }) {
                Column({ space: 5 }) {
                  Text('autoUILpx(40, 25)')
                    .fontColor(Color.Yellow)
                  DatePicker()
                    .width('33%')
                    .selectedTextStyle({ font: { size: autoUILpx(this.currentBreakPoint, 40, 25) } })
                    .disappearTextStyle({ font: { size: autoUILpx(this.currentBreakPoint, 40, 25) } })
                    .textStyle({ font: { size: autoUILpx(this.currentBreakPoint, 40, 25) } })
                }

                Column({ space: 5 }) {
                  Text('40lpx')
                    .fontColor(Color.Yellow)
                  DatePicker()
                    .width('33%')
                    .selectedTextStyle({ font: { size: '40lpx' } })
                    .disappearTextStyle({ font: { size: '40lpx' } })
                    .textStyle({ font: { size: '40lpx' } })
                }

                Column({ space: 5 }) {
                  Text('25lpx')
                    .fontColor(Color.Yellow)
                  DatePicker()
                    .width('33%')
                    .selectedTextStyle({ font: { size: '25lpx' } })
                    .disappearTextStyle({ font: { size: '25lpx' } })
                    .textStyle({ font: { size: '25lpx' } })
                }
              }
            }
          }
        }
        .width('100%')
        .height('60%')
        .backgroundColor('#ffbbf8e4')

        Text('跳转页面')
          .fontColor('333333')
          .fontSize(autoUILpx(this.currentBreakPoint, 50, 25))
          .onClick(() => {
            NavigationManager.getInstance().pushDetailPage('NextPage')
          })
      }
    }
    .backgroundColor('#fff')
  }
}