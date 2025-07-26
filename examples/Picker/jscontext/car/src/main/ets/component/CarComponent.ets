import { ComponentContent, LengthUnit } from '@kit.ArkUI';

globalThis.width = 10;

@Builder
function datePickerComponentBuilder(color: Color) {
  DatePickerComponent({});
}

@Builder
function datePickerDialogComponentBuilder(color: Color) {
  DatePickerDialogComponent({});
}

@Builder
function calendarPickerComponentBuilder(color: Color) {
  CalendarPickerComponent({});
}

@Builder
function calendarPickerDialogComponentBuilder(color: Color) {
  CalendarPickerDialogComponent({});
}

@Builder
function timePickerComponentBuilder(color: Color) {
  TimePickerComponent({});
}

@Builder
function timePickerDialogComponentBuilder(color: Color) {
  TimePickerDialogComponent({});
}

@Builder
function textPickerComponentBuilder(color: Color) {
  TextPickerComponent({});
}

@Builder
function textPickerDialogComponentBuilder(color: Color) {
  TextPickerDialogComponent({});
}

@Builder
function imageComponentBuilder(color: Color) {
  ImageComponent({});
}

@Builder
function imageAnimatorComponentBuilder(color: Color) {
  ImageAnimatorComponent({});
}

@Builder
function counterComponentBuilder(color: Color) {
  CounterComponent({});
}

@Builder
function patternLockComponentBuilder(color: Color) {
  PatternLockComponent({});
}

@Builder
function textClockComponentBuilder(color: Color) {
  TextClockComponent({});
}

@Builder
function textTimerComponentBuilder(color: Color) {
  TextTimerComponent({});
}

@Builder
function dataPanelComponentBuilder(color: Color) {
  DataPanelComponent({});
}

@Builder
function gaugeComponentBuilder(color: Color) {
  GaugeComponent({});
}

@Builder
function loadingprogressComponentBuilder(color: Color) {
  LoadingProgressComponent({});
}

@Builder
function progressComponentBuilder(color: Color) {
  ProgressComponent({});
}

@Builder
function qrCodeComponentBuilder(color: Color) {
  QRCodeComponent({});
}

@Builder
function badgeComponentBuilder(color: Color) {
  BadgeComponent({});
}

function printFields(obj: object) {
  let result: string = '';
  Object.keys(obj).forEach(key => {
    result += `${key}: ${obj[key]} `;
  });
  return result;
}

@Component
struct DatePickerComponent {
  @State isLunar: boolean = false;
  @State datePickerModeList: (DatePickerMode)[] = [
    DatePickerMode.DATE,
    DatePickerMode.YEAR_AND_MONTH,
    DatePickerMode.MONTH_AND_DAY,
  ];
  @State datePickerModeIndex: number = 0;
  private selectedDate: Date = new Date('2021-08-08');
  private onDateChange = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onDateChange times: ' + this.onDateChange;
  @State value3: string = 'onDateChange args: ';

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3
      ].join('\n')).backgroundColor(Color.Yellow)
      Button('切换公历农历')
        .margin({ top: 10, bottom: 10 })
        .onClick(() => {
          this.isLunar = !this.isLunar;
        })
      DatePicker({
        start: new Date('2020-1-1'),
        end: new Date('2030-1-1'),
        selected: this.selectedDate,
        mode: this.datePickerModeIndex
      })
        .lunar(this.isLunar)
        .onDateChange((value: Date) => {
          this.selectedDate = value;
          this.onDateChange++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value2 = 'onDateChange times: ' + this.onDateChange;
          this.value3 = 'onDateChange args: ' + value.toString();
        })
      Button('mode :' + this.datePickerModeIndex).margin({ top: 20 })
        .onClick(() => {
          this.datePickerModeIndex++;
          if (this.datePickerModeIndex >= this.datePickerModeList.length) {
            this.datePickerModeIndex = 0;
          }
        })
    }.width('100%')
  }
}

@Component
struct CalendarPickerComponent {
  private selectedDate: Date = new Date('2024-03-05');
  private onChange = 0;
  @State edgeAlignList: (CalendarAlign)[] = [
    CalendarAlign.START,
    CalendarAlign.CENTER,
    CalendarAlign.END,
  ];
  @State edgeAlignIndex: number = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onChange times: ' + this.onChange;
  @State value3: string = 'onChange args: ';

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3
      ].join('\n')).backgroundColor(Color.Yellow)
      Column() {
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
          .edgeAlign(this.edgeAlignIndex)
          .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
          .margin(10)
          .onChange((value: Date) => {
            this.onChange++;
            globalThis.width++;
            this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
            this.value2 = 'onChange times: ' + this.onChange;
            this.value3 = 'onChange args: ' + value.toString();
          })
      }.alignItems(HorizontalAlign.End).width('100%')

      Button('edgeAlign :' + this.edgeAlignIndex).margin({ top: 20 })
        .onClick(() => {
          this.edgeAlignIndex++;
          if (this.edgeAlignIndex >= this.edgeAlignList.length) {
            this.edgeAlignIndex = 0;
          }
        })
      Text('日历日期选择器').fontSize(30)
    }.width('100%')
  }
}

@Component
struct TimePickerComponent {
  @State isLoop: boolean = true;
  private selectedTime: Date = new Date('2022-07-22T08:00:00');
  private onChange = 0;
  private onEnterSelectedArea = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onChange times: ' + this.onChange;
  @State value3: string = 'onChange args: ';
  @State value4: string = 'onEnterSelectedArea times: ' + this.onEnterSelectedArea;
  @State value5: string = 'onEnterSelectedArea args: ';

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
        this.value4,
        this.value5
      ].join('\n')).backgroundColor(Color.Yellow)
      TimePicker({
        selected: this.selectedTime,
        format: TimePickerFormat.HOUR_MINUTE_SECOND,
        start: new Date('2022-07-22T08:30:00'),
        end: new Date('2022-07-22T15:20:00'),
      })
        .loop(this.isLoop)
        .useMilitaryTime(false)
        .disappearTextStyle({ color: '#004aaf', font: { size: 24, weight: FontWeight.Lighter } })
        .textStyle({ color: Color.Black, font: { size: 26, weight: FontWeight.Normal } })
        .selectedTextStyle({ color: Color.Blue, font: { size: 30, weight: FontWeight.Bolder } })
        .onEnterSelectedArea((value: TimePickerResult) => {
          this.onEnterSelectedArea++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value4 = 'onEnterSelectedArea times: ' + this.onEnterSelectedArea;
          this.value5 = 'onEnterSelectedArea args: ' + printFields(value);
        })
        .onChange((value: TimePickerResult) => {
          if (value.hour >= 0) {
            this.selectedTime.setHours(value.hour, value.minute);
          }
          this.onChange++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value2 = 'onChange times: ' + this.onChange;
          this.value3 = 'onChange args: ' + printFields(value);
        })
    }
  }
}

@Component
struct TextPickerComponent {
  @State isLoop: boolean = false;
  private select: number = 1;
  private fruits: string[] = ['apple1', 'orange2', 'peach3', 'grape4'];
  private onChange = 0;
  private onEnterSelectedArea = 0;
  private onScrollStop = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onChange times: ' + this.onChange;
  @State value3: string = 'onChange args: ';
  @State value4: string = 'onEnterSelectedArea times: ' + this.onEnterSelectedArea;
  @State value5: string = 'onEnterSelectedArea args: ';
  @State value6: string = 'onScrollStop times: ' + this.onScrollStop;
  @State value7: string = 'onScrollStop args: ';

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
        this.value4,
        this.value5,
        this.value6,
        this.value7
      ].join('\n')).backgroundColor(Color.Yellow)
      TextPicker({
        range: this.fruits,
        selected: this.select,
        value: this.fruits[this.select]
      })
        .onChange((value: string | string[], index: number | number[]) => {
          this.onChange++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value2 = 'onChange times: ' + this.onChange;
          this.value3 = 'onChange args: ' + value.toString() + ', ' + index.toString();
        })
        .onScrollStop((value: string | string[], index: number | number[]) => {
          this.onScrollStop++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value6 = 'onScrollStop times: ' + this.onScrollStop;
          this.value7 = 'onScrollStop args: ' + value.toString() + ', ' + index.toString();
        })
        .onEnterSelectedArea((value: string | string[], index: number | number[]) => {
          this.onEnterSelectedArea++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value4 = 'onEnterSelectedArea times: ' + this.onEnterSelectedArea;
          this.value5 = 'onEnterSelectedArea args: ' + value.toString() + ', ' + index.toString();
        })
        .disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } })
        .textStyle({ color: Color.Black, font: { size: 20, weight: FontWeight.Normal } })
        .selectedTextStyle({ color: Color.Blue, font: { size: 30, weight: FontWeight.Bolder } })
        .defaultPickerItemHeight(50)
        .canLoop(this.isLoop)
        .selectedIndex(2)
      Row() {
        Text('循环滚动').fontSize(20)

        Toggle({ type: ToggleType.Switch, isOn: false })
          .onChange((isOn: boolean) => {
            this.isLoop = isOn;
          })
      }.position({ x: '60%', y: '40%' })
    }.width('100%')
  }
}

@Component
struct DatePickerDialogComponent {
  selectedDate: Date = new Date('2010-1-1');
  @State isLunar: boolean = false;
  @State showTime: boolean = true;
  @State useMilitaryTime: boolean = false;
  private onDateAccept = 0;
  private onCancel = 0;
  private onDateChange = 0;
  private onDidAppear = 0;
  private onDidDisappear = 0;
  private onWillAppear = 0;
  private onWillDisappear = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onDateAccept times: ' + this.onDateAccept;
  @State value3: string = 'onDateAccept args: ';
  @State value4: string = 'onCancel times: ' + this.onCancel;
  @State value5: string = 'onDateChange times: ' + this.onDateChange;
  @State value6: string = 'onDateChange args: ';
  @State value7: string = 'onDidAppear times: ' + this.onDidAppear;
  @State value8: string = 'onDidDisappear times: ' + this.onDidDisappear;
  @State value9: string = 'onWillAppear times: ' + this.onWillAppear;
  @State value10: string = 'onWillDisappear times: ' + this.onWillDisappear;

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
        this.value4,
        this.value5,
        this.value6,
        this.value7,
        this.value8,
        this.value9,
        this.value10
      ].join('\n')).backgroundColor(Color.Yellow)
      Button('切换公历农历')
        .margin({ top: 10, bottom: 10 })
        .onClick(() => {
          this.isLunar = !this.isLunar;
        })
      Button('切换showTime')
        .margin({ top: 10, bottom: 10 })
        .onClick(() => {
          this.showTime = !this.showTime;
        })
      Button('切换useMilitaryTime')
        .margin({ top: 10, bottom: 10 })
        .onClick(() => {
          this.useMilitaryTime = !this.useMilitaryTime;
        })
      Button('DatePickerDialog')
        .margin(20)
        .onClick(() => {
          this.getUIContext().showDatePickerDialog({
            start: new Date('2000-1-1'),
            end: new Date('2100-12-31'),
            lunar: this.isLunar,
            selected: this.selectedDate,
            showTime: this.showTime,
            useMilitaryTime: this.useMilitaryTime,
            disappearTextStyle: { color: '#297bec', font: { size: '20fp', weight: FontWeight.Bold } },
            textStyle: { color: Color.Black, font: { size: '18fp', weight: FontWeight.Normal } },
            selectedTextStyle: { color: Color.Blue, font: { size: '26fp', weight: FontWeight.Regular } },
            dateTimeOptions: { hour: 'numeric', minute: '2-digit' },
            onDateAccept: (value: Date) => {
              // 通过Date的setFullYear方法设置按下确定按钮时的日期，这样当弹窗再次弹出时显示选中的是上一次确定的日期
              this.selectedDate = value
              this.onDateAccept++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value2 = 'onDateAccept times: ' + this.onDateAccept;
              this.value3 = 'onDateAccept args: ' + value.toString();
            },
            onCancel: () => {
              this.onCancel++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value4 = 'onCancel times: ' + this.onCancel;
            },
            onDateChange: (value: Date) => {
              this.onDateChange++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value5 = 'onDateChange times: ' + this.onDateChange;
              this.value6 = 'onDateChange args: ' + value.toString();
            },
            onDidAppear: () => {
              this.onDidAppear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value7 = 'onDidAppear times: ' + this.onDidAppear;
            },
            onDidDisappear: () => {
              this.onDidDisappear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value8 = 'onDidDisappear times: ' + this.onDidDisappear;
            },
            onWillAppear: () => {
              this.onWillAppear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value9 = 'onWillAppear times: ' + this.onWillAppear;
            },
            onWillDisappear: () => {
              this.onWillDisappear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value10 = 'onWillDisappear times: ' + this.onWillDisappear;
            }
          })
        })
    }.width('100%')
  }
}

@Component
struct CalendarPickerDialogComponent {
  private selectedDate: Date = new Date('2024-04-23');
  private onAccept = 0;
  private onCancel = 0;
  private onChange = 0;
  private onDidAppear = 0;
  private onDidDisappear = 0;
  private onWillAppear = 0;
  private onWillDisappear = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onAccept times: ' + this.onAccept;
  @State value3: string = 'onAccept args: ';
  @State value4: string = 'onCancel times: ' + this.onCancel;
  @State value5: string = 'onChange times: ' + this.onChange;
  @State value6: string = 'onChange args: ';
  @State value7: string = 'onDidAppear times: ' + this.onDidAppear;
  @State value8: string = 'onDidDisappear times: ' + this.onDidDisappear;
  @State value9: string = 'onWillAppear times: ' + this.onWillAppear;
  @State value10: string = 'onWillDisappear times: ' + this.onWillDisappear;

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
        this.value4,
        this.value5,
        this.value6,
        this.value7,
        this.value8,
        this.value9,
        this.value10
      ].join('\n')).backgroundColor(Color.Yellow)
      Button('Show CalendarPicker Dialog')
        .margin(10)
        .onClick(() => {
          console.info('CalendarDialog.show');
          CalendarPickerDialog.show({
            selected: this.selectedDate,
            backgroundColor: Color.Gray,
            backgroundBlurStyle: BlurStyle.NONE,
            shadow: ShadowStyle.OUTER_FLOATING_SM,
            onAccept: (value: Date) => {
              // 通过Date的setFullYear方法设置按下确定按钮时的日期，这样当弹窗再次弹出时显示选中的是上一次确定的日期
              this.selectedDate = value
              this.onAccept++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value2 = 'onAccept times: ' + this.onAccept;
              this.value3 = 'onAccept args: ' + value.toString();
            },
            onCancel: () => {
              this.onCancel++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value4 = 'onCancel times: ' + this.onCancel;
            },
            onChange: (value: Date) => {
              this.onChange++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value5 = 'onChange times: ' + this.onChange;
              this.value6 = 'onChange args: ' + value.toString();
            },
            onDidAppear: () => {
              this.onDidAppear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value7 = 'onDidAppear times: ' + this.onDidAppear;
            },
            onDidDisappear: () => {
              this.onDidDisappear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value8 = 'onDidDisappear times: ' + this.onDidDisappear;
            },
            onWillAppear: () => {
              this.onWillAppear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value9 = 'onWillAppear times: ' + this.onWillAppear;
            },
            onWillDisappear: () => {
              this.onWillDisappear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value10 = 'onWillDisappear times: ' + this.onWillDisappear;
            }
          });
        })
    }.width('100%')
  }
}

@Component
struct TimePickerDialogComponent {
  @State useMilitaryTime: boolean = false;
  private selectTime: Date = new Date('2020-12-25T08:30:00');
  private onAccept = 0;
  private onCancel = 0;
  private onChange = 0;
  private onDidAppear = 0;
  private onDidDisappear = 0;
  private onWillAppear = 0;
  private onWillDisappear = 0;
  private onEnterSelectedArea = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onAccept times: ' + this.onAccept;
  @State value3: string = 'onAccept args: ';
  @State value4: string = 'onCancel times: ' + this.onCancel;
  @State value5: string = 'onChange times: ' + this.onChange;
  @State value6: string = 'onChange args: ';
  @State value7: string = 'onDidAppear times: ' + this.onDidAppear;
  @State value8: string = 'onDidDisappear times: ' + this.onDidDisappear;
  @State value9: string = 'onWillAppear times: ' + this.onWillAppear;
  @State value10: string = 'onWillDisappear times: ' + this.onWillDisappear;
  @State value11: string = 'onEnterSelectedArea times: ' + this.onEnterSelectedArea;
  @State value12: string = 'onEnterSelectedArea times: ' + this.onEnterSelectedArea;

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
        this.value4,
        this.value5,
        this.value6,
        this.value7,
        this.value8,
        this.value9,
        this.value10,
        this.value11,
        this.value12

      ].join('\n')).backgroundColor(Color.Yellow)
      Button('切换useMilitaryTime')
        .margin({ top: 10, bottom: 10 })
        .onClick(() => {
          this.useMilitaryTime = !this.useMilitaryTime;
        })
      Button('TimePickerDialog')
        .margin(20)
        .onClick(() => {
          this.getUIContext().showTimePickerDialog({
            selected: this.selectTime,
            format: TimePickerFormat.HOUR_MINUTE,
            useMilitaryTime: this.useMilitaryTime,
            dateTimeOptions: { hour: 'numeric', minute: '2-digit' },
            disappearTextStyle: { color: '#297bec', font: { size: '20fp', weight: FontWeight.Bold } },
            textStyle: { color: Color.Black, font: { size: '18fp', weight: FontWeight.Normal } },
            selectedTextStyle: { color: Color.Blue, font: { size: '26fp', weight: FontWeight.Regular } },
            onAccept: (value: TimePickerResult) => {
              // 设置selectTime为按下确定按钮时的时间，这样当弹窗再次弹出时显示选中的为上一次确定的时间
              if (value.hour != undefined && value.minute != undefined) {
                this.selectTime.setHours(value.hour, value.minute);
              }
              this.onAccept++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value2 = 'onAccept times: ' + this.onAccept;
              this.value3 = 'onAccept args: ' + printFields(value);
            },
            onCancel: () => {
              this.onCancel++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value4 = 'onCancel times: ' + this.onCancel;
            },
            onChange: (value: TimePickerResult) => {
              this.onChange++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value5 = 'onChange times: ' + this.onChange;
              this.value6 = 'onChange args: ' + printFields(value);
            },
            onDidAppear: () => {
              this.onDidAppear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value7 = 'onDidAppear times: ' + this.onDidAppear;
            },
            onDidDisappear: () => {
              this.onDidDisappear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value8 = 'onDidDisappear times: ' + this.onDidDisappear;
            },
            onWillAppear: () => {
              this.onWillAppear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value9 = 'onWillAppear times: ' + this.onWillAppear;
            },
            onWillDisappear: () => {
              this.onWillDisappear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value10 = 'onWillDisappear times: ' + this.onWillDisappear;
            },
            onEnterSelectedArea: (value: TimePickerResult) => {
              this.onEnterSelectedArea++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value11 = 'onEnterSelectedArea times: ' + this.onEnterSelectedArea;
              this.value12 = 'onEnterSelectedArea args: ' + printFields(value);
            }
          });
        })
    }.width('100%')
  }
}

@Component
struct TextPickerDialogComponent {
  private select: number | number[] = 0;
  private fruits: string[] = ['apple1', 'orange2', 'peach3', 'grape4', 'banana5'];
  @State v: string = '';
  private onAccept = 0;
  private onCancel = 0;
  private onChange = 0;
  private onDidAppear = 0;
  private onDidDisappear = 0;
  private onWillAppear = 0;
  private onWillDisappear = 0;
  private onScrollStop = 0;
  private onEnterSelectedArea = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onAccept times: ' + this.onAccept;
  @State value3: string = 'onAccept args: ';
  @State value4: string = 'onCancel times: ' + this.onCancel;
  @State value5: string = 'onChange times: ' + this.onChange;
  @State value6: string = 'onChange args: ';
  @State value7: string = 'onDidAppear times: ' + this.onDidAppear;
  @State value8: string = 'onDidDisappear times: ' + this.onDidDisappear;
  @State value9: string = 'onWillAppear times: ' + this.onWillAppear;
  @State value10: string = 'onWillDisappear times: ' + this.onWillDisappear;
  @State value11: string = 'onScrollStop times: ' + this.onScrollStop;
  @State value12: string = 'onScrollStop args: ';
  @State value13: string = 'onEnterSelectedArea times: ' + this.onEnterSelectedArea;
  @State value14: string = 'onEnterSelectedArea times: ' + this.onEnterSelectedArea;

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
        this.value4,
        this.value5,
        this.value6,
        this.value7,
        this.value8,
        this.value9,
        this.value10,
        this.value11,
        this.value12
      ].join('\n')).backgroundColor(Color.Yellow)
      Button('TextPickerDialog:' + this.v)
        .margin(10)
        .onClick(() => {
          this.getUIContext().showTextPickerDialog({
            range: this.fruits,
            selected: this.select,
            value: this.v,
            defaultPickerItemHeight: 50,
            disappearTextStyle: { color: '#297bec', font: { size: '20fp', weight: FontWeight.Bold } },
            textStyle: { color: Color.Black, font: { size: '18fp', weight: FontWeight.Normal } },
            selectedTextStyle: { color: Color.Blue, font: { size: '26fp', weight: FontWeight.Regular } },
            onAccept: (value: TextPickerResult) => {
              // 设置select为按下确定按钮时候的选中项index，这样当弹窗再次弹出时显示选中的是上一次确定的选项
              this.select = value.index;
              console.log(this.select + '');
              // 点击确定后，被选到的文本数据展示到页面
              this.v = value.value as string;
              this.onAccept++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value2 = 'onAccept times: ' + this.onAccept;
              this.value3 = 'onAccept args: ' + printFields(value);
            },
            onCancel: () => {
              this.onCancel++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value4 = 'onCancel times: ' + this.onCancel;
            },
            onChange: (value: TextPickerResult) => {
              this.onChange++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value5 = 'onChange times: ' + this.onChange;
              this.value6 = 'onChange args: ' + printFields(value);
            },
            onScrollStop: (value: TextPickerResult) => {
              this.onScrollStop++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value11 = 'onScrollStop times: ' + this.onScrollStop;
              this.value12 = 'onScrollStop args: ' + printFields(value);
            },
            onDidAppear: () => {
              this.onDidAppear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value7 = 'onDidAppear times: ' + this.onDidAppear;
            },
            onDidDisappear: () => {
              this.onDidDisappear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value8 = 'onDidDisappear times: ' + this.onDidDisappear;
            },
            onWillAppear: () => {
              this.onWillAppear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value9 = 'onWillAppear times: ' + this.onWillAppear;
            },
            onWillDisappear: () => {
              this.onWillDisappear++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value10 = 'onWillDisappear times: ' + this.onWillDisappear;
            },
            onEnterSelectedArea: (value: TextPickerResult) => {
              this.onEnterSelectedArea++;
              globalThis.width++;
              this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
              this.value13 = 'onEnterSelectedArea times: ' + this.onEnterSelectedArea;
              this.value14 = 'onEnterSelectedArea args: ' + printFields(value);
            },
          });
        })
    }.width('100%')
  }
}

interface onImageComplete {
  width: number;
  height: number;
  componentWidth: number;
  componentHeight: number;
  loadingStatus: number;
  contentWidth: number;
  contentHeight: number;
  contentOffsetX: number;
  contentOffsetY: number;
}

@Component
struct ImageComponent {
  private imageOne: Resource = $r('app.media.startIcon');
  private imageTwo: Resource = $r('app.media.hello');
  private imageThree: Resource = $r('app.media.layered_image');
  @State objectFit: ImageFit = ImageFit.Contain;
  @State sourceSize: number = 20;
  @State copy: CopyOptions = CopyOptions.InApp;
  @State drm: DynamicRangeMode = DynamicRangeMode.HIGH;
  @State orientation: ImageRotateOrientation = ImageRotateOrientation.AUTO;
  @State src: Resource = this.imageOne;
  @State src2: Resource = this.imageOne;
  private onComplete = 0;
  private onError = 0;
  private onFinish = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onComplete times: ' + this.onComplete;
  @State value3: string = 'onComplete args: ';
  @State value4: string = 'onError times: ' + this.onError;
  @State value5: string = 'onError args: ';
  @State value6: string = 'onFinish times: ' + this.onFinish;

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
        this.value4,
        this.value5,
        this.value6,
      ].join('\n')).backgroundColor(Color.Yellow)
      // 为图片添加点击事件，点击完成后加载特定图片
      Text('点击图片，触发onError').backgroundColor(Color.Blue)
      Row() {
        Button('切换objectFit:' + this.objectFit)
          .onClick(() => {
            this.objectFit++;
            this.objectFit = this.objectFit % 17;
          })
        Button('变换sourceSize:' + this.sourceSize)
          .onClick(() => {
            if (this.sourceSize == 20) {
              this.sourceSize = 50;
            } else {
              this.sourceSize = 20;
            }
          })
      }

      Row() {
        Button('图片可复制:' + this.copy)
          .onClick(() => {
            if (this.copy == 0) {
              this.copy = 1;
            } else {
              this.copy = 0;
            }
          })
      }

      Row() {
        Button('DynamicRangeMode:' + this.drm)
          .onClick(() => {
            this.drm++;
            this.drm %= 3;
          })
        Button('orientation:' + this.orientation)
          .onClick(() => {
            this.orientation++;
            this.orientation %= 9;
          })
      }

      Image(this.src)
        .width(100)
        .height(100)
        .onClick(() => {
          this.src = this.imageThree;
        })
        .copyOption(this.copy)
        .alt($r('app.media.background'))
        .objectFit(this.objectFit)
        .dynamicRangeMode(this.drm)
        .orientation(this.orientation)
        .sourceSize({ width: this.sourceSize, height: this.sourceSize })
        .onError((error: ImageError) => {
          this.onError++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value4 = 'onError times: ' + this.onError;
          this.value5 = 'onError args: ' + printFields(error);
        })
        .onComplete((value: onImageComplete) => {
          this.onComplete++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value2 = 'onComplete times: ' + this.onComplete;
          this.value3 = 'onComplete args: ' + printFields(value);
        })

      // 当加载图片为SVG格式时
      Button('点击播放svg')
        .onClick(() => {
          this.src2 = this.imageTwo;
        })
      Button('重置图片')
        .onClick(() => {
          this.src2 = this.imageOne;
        })
      Text('不设置fillColor')
      Image(this.src2)
        .width(100)
        .height(100)
        .onComplete((value: onImageComplete) => {
          this.onComplete++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value2 = 'onComplete times: ' + this.onComplete;
          this.value3 = 'onComplete args: ' + printFields(value);
        })
        .onError((error: ImageError) => {
          this.onError++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value4 = 'onError times: ' + this.onError;
          this.value5 = 'onError args: ' + printFields(error);
        })
        .onFinish(() => {
          this.onFinish++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value6 = 'onFinish times: ' + this.onFinish;
        })
      Text('fillColor传入Color.Blue')
      Image(this.src2)
        .height(100)
        .width(100)
        .objectFit(ImageFit.Contain)
        .borderWidth(1)
        .fillColor(Color.Blue)
    }.width('100%')
  }
}

@Component
struct ImageAnimatorComponent {
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State reverse: boolean = false;
  @State iterations: number = 1;
  @State fixedSize: boolean = true;
  @State monitorInvisibleArea: boolean = false;
  private onStart = 0;
  private onPause = 0;
  private onRepeat = 0;
  private onCancel = 0;
  private onFinish = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onStart times: ' + this.onStart;
  @State value3: string = 'onPause times: ' + this.onPause;
  @State value4: string = 'onRepeat times: ' + this.onRepeat;
  @State value5: string = 'onCancel times: ' + this.onCancel;
  @State value6: string = 'onFinish times: ' + this.onFinish;

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
        this.value4,
        this.value5,
        this.value6,
      ].join('\n')).backgroundColor(Color.Yellow)
      Button('切换fixedSize:' + this.fixedSize)
        .margin(10)
        .onClick(() => {
          this.fixedSize = !this.fixedSize;
        })
      Button('切换monitorInvisibleArea:' + this.monitorInvisibleArea)
        .onClick(() => {
          this.monitorInvisibleArea = !this.monitorInvisibleArea;
        })
      ImageAnimator()
        .images([
          {
            src: $r('app.media.startIcon')
          },
          {
            src: $r('app.media.ohos_ic_normal_white_grid_mp3')
          },
          {
            src: $r('app.media.ohos_ic_normal_white_grid_image')
          },
          {
            src: $r('app.media.ohos_ic_normal_white_grid_html')
          },
          {
            src: $r('app.media.ohos_ic_normal_white_grid_folder')
          },
          {
            src: $r('app.media.ohos_ic_normal_white_grid_doc')
          },
          {
            src: $r('app.media.ohos_ic_normal_white_grid_compress')
          },
          {
            src: $r('app.media.ohos_ic_normal_white_grid_calendar')
          },
          {
            src: $r('app.media.ohos_ic_normal_white_grid_audio')
          },
          {
            src: $r('app.media.background')
          }
        ])
        .duration(2000)
        .fixedSize(this.fixedSize)
        .state(this.state)
        .reverse(this.reverse)
        .fillMode(FillMode.None)
        .iterations(this.iterations)
        .monitorInvisibleArea(this.monitorInvisibleArea)
        .width(100)
        .height(100)
        .onStart(() => {
          this.onStart++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value2 = 'onStart times: ' + this.onStart;
        })
        .onPause(() => {
          this.onPause++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value3 = 'onPause times: ' + this.onPause;
        })
        .onRepeat(() => {
          this.onRepeat++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value4 = 'onRepeat times: ' + this.onRepeat;
        })
        .onCancel(() => {
          this.onCancel++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value5 = 'onCancel times: ' + this.onCancel;
        })
        .onFinish(() => {
          this.onFinish++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value6 = 'onFinish times: ' + this.onFinish;
          this.state = AnimationStatus.Stopped
        })
      Row() {
        Button('start').width(100).padding(5).onClick(() => {
          this.state = AnimationStatus.Running
        }).margin(5)
        Button('pause').width(100).padding(5).onClick(() => {
          this.state = AnimationStatus.Paused // 显示当前帧图片
        }).margin(5)
        Button('stop').width(100).padding(5).onClick(() => {
          this.state = AnimationStatus.Stopped // 显示动画的起始帧图片
        }).margin(5)
      }

      Row() {
        Button('reverse').width(100).padding(5).onClick(() => {
          this.reverse = !this.reverse
        }).margin(5)
        Button('cancel').width(100).padding(5).onClick(() => {
          this.state = AnimationStatus.Initial
        }).margin(5)
        Button('iterations: ' + this.iterations).width(100).padding(5).onClick(() => {
          this.iterations ++ // 无限循环播放
          if (this.iterations == 10 ) {
            this.iterations = -1;
          }
          if (this.iterations == 0 ) {
            this.iterations = 1;
          }
        }).margin(5)
      }
    }.width('100%')
  }
}

@Component
struct CounterComponent {
  @State value: number = 0;
  private onInc = 0;
  private onDec = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onInc times: ' + this.onInc;
  @State value3: string = 'onDec times: ' + this.onDec;

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
      ].join('\n')).backgroundColor(Color.Yellow)
      Counter() {
        Text(this.value.toString())
      }
      .onInc(() => {
        this.value++;
        this.onInc++;
        globalThis.width++;
        this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
        this.value2 = 'onInc times: ' + this.onInc;
      })
      .onDec(() => {
        this.value--;
        this.onDec++;
        globalThis.width++;
        this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
        this.value3 = 'onDec times: ' + this.onDec;
      })
    }.width('100%')
  }
}

@Component
struct PatternLockComponent {
  @State passwords: Number[] = [];
  @State message: string = 'please input password!';
  private patternLockController: PatternLockController = new PatternLockController();
  private onDotConnect = 0;
  private onPatternComplete = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onDotConnect times: ' + this.onDotConnect;
  @State value3: string = 'onDotConnect args: ';
  @State value4: string = 'onPatternComplete times: ' + this.onPatternComplete;
  @State value5: string = 'onPatternComplete args: ';

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
        this.value4,
        this.value5,
      ].join('\n')).backgroundColor(Color.Yellow)
      Text(this.message).textAlign(TextAlign.Center).margin(20).fontSize(20)
      PatternLock(this.patternLockController)
        .sideLength(200)
        .circleRadius(9)
        .pathStrokeWidth(5)
        .regularColor('#551823')
        .activeColor('#707070')
        .selectedColor('#707070')
        .pathColor('#707070')
        .backgroundColor('#F5F5F5')
        .autoReset(true)
        .activateCircleStyle({
          color: '#707070',
          radius: { value: 16, unit: LengthUnit.VP },
          enableWaveEffect: true
        })
        .onDotConnect((index: number) => {
          this.onDotConnect++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value2 = 'onDotConnect times: ' + this.onDotConnect;
          this.value3 = 'onDotConnect args: ' + index.toString();
        })
        .onPatternComplete((input: Array<number>) => {
          // 输入的密码长度小于5时，提示重新输入
          if (input.length < 5) {
            this.message = 'The password length needs to be greater than 5, please enter again.';
            return;
          }
          // 判断密码长度是否大于0
          if (this.passwords.length > 0) {
            // 判断两次输入的密码是否相同，相同则提示密码设置成功，否则提示重新输入
            if (this.passwords.toString() === input.toString()) {
              this.passwords = input;
              this.message = 'Set password successfully: ' + this.passwords.toString();
              this.patternLockController.setChallengeResult(PatternLockChallengeResult.CORRECT);
            } else {
              this.message = 'Inconsistent passwords, please enter again.';
              this.patternLockController.setChallengeResult(PatternLockChallengeResult.WRONG);
            }
          } else {
            // 提示第二次输入密码
            this.passwords = input;
            this.message = 'Please enter again.';
          }
          this.onPatternComplete++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value4 = 'onPatternComplete times: ' + this.onPatternComplete;
          this.value5 = 'onPatternComplete args: ' + input.toString();
        })
      Button('Reset PatternLock').margin(30).onClick(() => {
        // 重置密码锁
        this.patternLockController.reset();
        this.passwords = [];
        this.message = 'Please input password';
      })
    }.width('100%')
  }
}

@Component
struct TextClockComponent {
  @State accumulateTime: number = 0;
  // 导入对象
  controller: TextClockController = new TextClockController();
  private onDateChange = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onDateChange times: ' + this.onDateChange;
  @State value3: string = 'onDateChange args: ';

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
      ].join('\n')).backgroundColor(Color.Yellow)
      Text('Current milliseconds is ' + this.accumulateTime)
        .fontSize(20)
      // 以12小时制显示东八区的系统时间，精确到秒。
      TextClock({ timeZoneOffset: -8, controller: this.controller })
        .format('aa hh:mm:ss')
        .onDateChange((value: number) => {
          this.accumulateTime = value;
          this.onDateChange++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value2 = 'onDateChange times: ' + this.onDateChange;
          this.value3 = 'onDateChange args: ' + value.toString();
        })
        .margin(20)
        .fontSize(30)
        .fontStyle(FontStyle.Italic)
        .fontColor(Color.Brown)
      Button('start TextClock')
        .margin({ bottom: 10 })
        .onClick(() => {
          // 启动文本时钟
          this.controller.start();
        })
      Button('stop TextClock')
        .onClick(() => {
          // 停止文本时钟
          this.controller.stop();
        })
    }
    .width('100%')
  }
}

@Component
struct TextTimerComponent {
  textTimerController: TextTimerController = new TextTimerController();
  @State format: string = 'mm:ss.SS';
  private onTimer = 0;
  @State value1: string = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
  @State value2: string = 'onTimer times: ' + this.onTimer;
  @State value3: string = 'onTimer args: ';

  build() {
    Column() {
      Divider()
      Text('回调情况')
      Text([
        this.value1,
        this.value2,
        this.value3,
      ].join('\n')).backgroundColor(Color.Yellow)
      TextTimer({ isCountDown: true, count: 30000, controller: this.textTimerController })
        .format(this.format)
        .fontColor(Color.Black)
        .fontSize(50)
        .fontStyle(FontStyle.Italic)
        .onTimer((utc: number, elapsedTime: number) => {
          this.onTimer++;
          globalThis.width++;
          this.value1 = 'globalThis.width: ' + (globalThis.width ?? 'undefined');
          this.value2 = 'onTimer times: ' + this.onTimer;
          this.value3 = 'onTimer args: ' + utc.toString() + ', ' + elapsedTime.toString();
        })
      Row() {
        Button('start').onClick(() => {
          this.textTimerController.start();
        })
        Button('pause').onClick(() => {
          this.textTimerController.pause();
        })
        Button('reset').onClick(() => {
          this.textTimerController.reset();
        })
      }
    }
  }
}

@Component
struct DataPanelComponent {
  public values1: number[] = [20, 20, 20, 20]
  public color1: LinearGradient =
    new LinearGradient([{ color: '#65EEC9A3', offset: 0 }, { color: '#FFEF629F', offset: 1 }])
  public color2: LinearGradient =
    new LinearGradient([{ color: '#FF67F9D4', offset: 0 }, { color: '#FFFF9554', offset: 1 }])
  public colorShadow1: LinearGradient =
    new LinearGradient([{ color: '#65EEC9A3', offset: 0 }, { color: '#65EF629F', offset: 1 }])
  public colorShadow2: LinearGradient =
    new LinearGradient([{ color: '#65e26709', offset: 0 }, { color: '#65efbd08', offset: 1 }])
  public colorShadow3: LinearGradient =
    new LinearGradient([{ color: '#6572B513', offset: 0 }, { color: '#6508efa6', offset: 1 }])
  public colorShadow4: LinearGradient =
    new LinearGradient([{ color: '#65ed08f5', offset: 0 }, { color: '#65ef0849', offset: 1 }])
  @State color3: string = '#00FF00'
  @State color4: string = '#20FF0000'
  @State bgColor: string = '#08182431'
  @State offsetX: number = 15
  @State offsetY: number = 15
  @State radius: number = 5
  @State colorArray: Array<LinearGradient | ResourceColor> = [this.color1, this.color2, this.color3, this.color4]
  @State shadowColorArray: Array<LinearGradient | ResourceColor> =
    [this.colorShadow1, this.colorShadow2, this.colorShadow3, this.colorShadow4]

  build() {
    Column() {
      Divider()
      Text('LinearGradient')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .textAlign(TextAlign.Start)
        .width('100%')
        .margin({ top: 20, left: 20 })
      DataPanel({ values: this.values1, max: 100, type: DataPanelType.Circle })
        .width(300)
        .height(300)
        .valueColors(this.colorArray)
        .trackShadow({
          radius: this.radius,
          colors: this.shadowColorArray,
          offsetX: this.offsetX,
          offsetY: this.offsetY
        })
        .strokeWidth(30)
        .trackBackgroundColor(this.bgColor)
    }.width('100%')
  }
}

@Component
struct GaugeComponent {
  @State desc: string = '说明文本';

  @Builder
  descriptionBuilder() {
    Text(this.desc)
      .maxFontSize('30sp')
      .minFontSize('10.0vp')
      .fontColor('#fffa2a2d')
      .fontWeight(FontWeight.Medium)
      .width('100%')
      .textAlign(TextAlign.Center)
  }

  build() {
    Column() {
      Divider()
      Button('修改文本').onClick(() => {
        this.desc = '修改成功';
      })
      Gauge({ value: 50, min: 1, max: 100 }) {
        Column() {
        }.width('100%')
      }
      .value(50)
      .startAngle(210)
      .endAngle(150)
      .colors([[new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
        [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
        [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
        [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
        [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
        [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
        [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
        [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
        [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]), 1]])
      .width('80%')
      .strokeWidth(18)
      .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
      .description(this.descriptionBuilder)
      .padding(18)
    }.width('100%')
  }
}

@Component
struct LoadingProgressComponent {
  @State enableLoading: boolean = true;

  build() {
    Column() {
      Divider()
      Button('切换enableLoading').onClick(() => {
        this.enableLoading = !this.enableLoading;
      })
      Text('Orbital LoadingProgress ').fontSize(9).fontColor(0xCCCCCC).width('90%')
      LoadingProgress()
        .color(Color.Blue)
        .enableLoading(this.enableLoading)
        .layoutWeight(1)
    }.width('100%')
  }
}

@Component
struct ProgressComponent {
  @State enableSmoothEffect: boolean = true;
  @State value: number = 0;

  build() {
    Column() {
      Divider()
      Text('Linear Progress').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Progress({ value: 10, type: ProgressType.Linear }).width(200)
      Progress({ value: 20, total: 150, type: ProgressType.Linear }).color(Color.Grey).value(50).width(200)


      Text('ScaleRing Progress').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Text('enableSmoothEffect: true')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('90%')
        .margin(5)
        .margin({ top: 20 })
      Progress({ value: this.value, total: 100, type: ProgressType.ScaleRing })
        .style({ strokeWidth: 10, enableSmoothEffect: true })

      Text('enableSmoothEffect: false').fontSize(9).fontColor(0xCCCCCC).width('90%').margin(5)
      Progress({ value: this.value, total: 100, type: ProgressType.ScaleRing })
        .style({ strokeWidth: 10, enableSmoothEffect: false })

      Button('value +10').onClick(() => {
        this.value += 10;
      })
        .width(75)
        .height(15)
        .fontSize(9)
    }.width('100%')
  }
}

@Component
struct QRCodeComponent {
  private value: string = 'hello world';

  build() {
    Column() {
      Divider()
      RelativeContainer() {
        Image($r('app.media.startIcon'))
        // 设置二维码背景色为透明
        QRCode(this.value).width(200).height(200).backgroundColor('#00ffffff')
      }.width(200).height(200)
    }.width('100%').margin({ top: 5 })
  }
}

@Component
struct BadgeComponent {
  @State badgeCount: number = 1;

  build() {
    Column() {
      Divider()
      Badge({
        count: this.badgeCount,
        maxCount: 10,
        style: {},
        position: BadgePosition.RightTop,
      }) {
        Image($r('app.media.startIcon'))
          .width(50)
          .height(50)
      }
      .width(55)

      Button('count --').onClick(() => {
        this.badgeCount--;
      })
      Button('count ++').onClick(() => {
        this.badgeCount++;
      })
    }
    .margin({ top: 20 })
  }
}

export function InitBuilder1(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(datePickerComponentBuilder), color);
}

export function InitBuilder2(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(calendarPickerComponentBuilder), color);
}

export function InitBuilder3(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(timePickerComponentBuilder), color);
}

export function InitBuilder4(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(textPickerComponentBuilder), color);
}

export function InitBuilder5(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(datePickerDialogComponentBuilder), color);
}

export function InitBuilder6(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(calendarPickerDialogComponentBuilder), color);
}

export function InitBuilder7(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(timePickerDialogComponentBuilder), color);
}

export function InitBuilder8(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(textPickerDialogComponentBuilder), color);
}

export function InitBuilder9(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(imageComponentBuilder), color);
}

export function InitBuilder10(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(imageAnimatorComponentBuilder), color);
}

export function InitBuilder11(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(counterComponentBuilder), color);
}

export function InitBuilder12(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(patternLockComponentBuilder), color);
}

export function InitBuilder13(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(textClockComponentBuilder), color);
}

export function InitBuilder14(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(textTimerComponentBuilder), color);
}

export function InitBuilder15(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(dataPanelComponentBuilder), color);
}

export function InitBuilder16(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(gaugeComponentBuilder), color);
}

export function InitBuilder17(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(loadingprogressComponentBuilder), color);
}

export function InitBuilder18(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(progressComponentBuilder), color);
}

export function InitBuilder19(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(qrCodeComponentBuilder), color);
}

export function InitBuilder20(context: UIContext, color: Color) {
  return new ComponentContent<Color>(context,
    wrapBuilder<[Color]>(badgeComponentBuilder), color);
}