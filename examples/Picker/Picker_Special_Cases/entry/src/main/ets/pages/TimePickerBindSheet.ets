/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

@Entry
@Component
struct TimePickerDirty {
  @State isShow: boolean = false;
  @State sheetHeight: number = 300;
  @State isMilitaryTime: boolean = false;
  private selectedTime: Date = new Date('2022-07-22T08:00:00');
  @State isLunar: boolean = false;
  @State accumulateTime: number = 0;
  @State customPopup: boolean = false;

  @Builder
  myBuilder() {
    Column() {
      TimePicker({
        selected: this.selectedTime
      })
        .useMilitaryTime(this.isMilitaryTime)
        .onChange((value: TimePickerResult) => {
          if (value.hour >= 0) {
            this.selectedTime.setHours(value.hour, value.minute);
            console.info('select current time is: ' + JSON.stringify(value));
          }
        })
        .onEnterSelectedArea((value: TimePickerResult) => {
          console.info('item enter selected area, time is: ' + JSON.stringify(value));
        })
        .visibility(this.isShow ? Visibility.Visible : Visibility.None)
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  popupBuilder() {
    Column({ space: 2 }) {
      TimePicker({
        selected: this.selectedTime
      })
        .useMilitaryTime(this.isMilitaryTime)
        .onChange((value: TimePickerResult) => {
          if (value.hour >= 0) {
            this.selectedTime.setHours(value.hour, value.minute);
            console.info('select current time is: ' + JSON.stringify(value));
          }
        })
        .onEnterSelectedArea((value: TimePickerResult) => {
          console.info('item enter selected area, time is: ' + JSON.stringify(value));
        })
        .visibility(Visibility.None)
    }.width(300).height(300).padding(5)
  }

  build() {
    Column() {
      TimePicker({
        selected: this.selectedTime
      })
        .useMilitaryTime(this.isMilitaryTime)
        .onChange((value: TimePickerResult) => {
          if (value.hour >= 0) {
            this.selectedTime.setHours(value.hour, value.minute);
            console.info('select current time is: ' + JSON.stringify(value));
          }
        })
        .onEnterSelectedArea((value: TimePickerResult) => {
          console.info('item enter selected area, time is: ' + JSON.stringify(value));
        })
        .visibility(this.isShow ? Visibility.Visible : Visibility.None)
      Button('Visible switch')
        .onClick(() => {
          this.isShow = !this.isShow;
        })

      Button('transition modal 1')
        .onClick(() => {
          this.customPopup = !this.customPopup;
        })
        .fontSize(20)
        .margin(10)
        .bindPopup(this.customPopup, {
          builder: this.popupBuilder,
          placement: Placement.Top,
          mask: { color: '#33000000' },
          popupColor: Color.Yellow,
          enableArrow: true,
          keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,
          showInSubWindow: false,
          onStateChange: (e) => {
            if (!e.isVisible) {
              this.customPopup = false;
            }
          }
        })

      Button('transition modal 1')
        .onClick(() => {
          this.isShow = !this.isShow;
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShow, this.myBuilder(), {
          height: this.sheetHeight,
          showClose: true,
          backgroundColor: Color.Green,
          onWillAppear: () => {
            console.log('BindSheet onWillAppear()');
          },
          onAppear: () => {
            console.log('BindSheet onAppear()');
          },
          onWillDisappear: () => {
            console.log('BindSheet onWillDisappear()');
          },
          onDisappear: () => {
            console.log('BindSheet onDisappear()');
          }
        })
    }
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .height('100%')
  }
}