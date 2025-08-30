import { AlertDialog, LengthUnit } from '@kit.ArkUI';

globalThis.width = 10;

function printFields(obj: object) {
  let result: string = '';
  Object.keys(obj).forEach(key => {
    result += `${key}: ${obj[key]} `;
  });
  return result;
}

@Component
export struct DatePickerComponent {
  @State isLunar: boolean = false;
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
      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2100-1-1'),
        selected: this.selectedDate
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
    }.width('100%')
  }
}

@Component
export struct CalendarPickerComponent {
  private selectedDate: Date = new Date('2024-03-05');
  private onChange = 0;
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
          .edgeAlign(CalendarAlign.END)
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

      Text('日历日期选择器').fontSize(30)
    }.width('100%')
  }
}

@Component
export struct TimePickerComponent {
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
        selected: this.selectedTime
      })
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
export struct TextPickerComponent {
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
        .canLoop(false)
        .selectedIndex(2)
    }.width('100%')
  }
}

@Component
export struct DatePickerDialogComponent {
  selectedDate: Date = new Date('2010-1-1');
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
      Button('DatePickerDialog')
        .margin(20)
        .onClick(() => {
          this.getUIContext().showDatePickerDialog({
            start: new Date('2000-1-1'),
            end: new Date('2100-12-31'),
            selected: this.selectedDate,
            showTime: true,
            useMilitaryTime: false,
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
export struct CalendarPickerDialogComponent {
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
        .margin(20)
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
export struct TimePickerDialogComponent {
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
      Button('TimePickerDialog 12小时制')
        .margin(20)
        .onClick(() => {
          this.getUIContext().showTimePickerDialog({
            selected: this.selectTime,
            format: TimePickerFormat.HOUR_MINUTE,
            useMilitaryTime: false,
            dateTimeOptions: { hour: 'numeric', minute: '2-digit' },
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
export struct TextPickerDialogComponent {
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
        .margin(20)
        .onClick(() => {
          this.getUIContext().showTextPickerDialog({
            range: this.fruits,
            selected: this.select,
            value: this.v,
            defaultPickerItemHeight: 40,
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
export struct ImageComponent {
  private imageOne: Resource = $r('app.media.startIcon');
  private imageTwo: Resource = $r('app.media.hello');
  private imageThree: Resource = $r('app.media.layered_image');
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
      Image(this.src)
        .width(100)
        .height(100)
        .onClick(() => {
          this.src = this.imageThree;
        })
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
    }.width('100%')
  }
}

@Component
export struct ImageAnimatorComponent {
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
export struct CounterComponent {
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
export struct PatternLockComponent {
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
export struct TextClockComponent {
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
export struct TextTimerComponent {
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