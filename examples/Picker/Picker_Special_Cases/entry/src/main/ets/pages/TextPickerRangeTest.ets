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
 
import { common } from '@kit.AbilityKit'

@CustomDialog
struct DatePickerDialog {
  controller?: CustomDialogController
  @State range: string[][] = []
  @State selected: number[] = []
  current: Date = new Date()
  context = getContext(this) as common.UIAbilityContext

  getStartDate() {
    return new Date('1799-01-01')
  }

  getEndDate() {
    return new Date('2099-12-31');
  }

  aboutToAppear() {
    const currentDate = new Date()
    const range = this.generateDateRange( currentDate)
    this.range = range
    const currentYearIndex = range[0].indexOf(`${currentDate.getFullYear()}`)

    this.selected = [currentYearIndex, currentDate.getMonth(), currentDate.getDate() - 1]

  }

  generateDateRange(currentDate: Date) {
    let years: string[] = []
    const startDate = this.getStartDate()
    const endDate = this.getEndDate()

    for (let i = startDate.getFullYear(); i <= endDate.getFullYear(); i++) {
      years.push(`${i}`)
    }

    const months: string[] = []

    for (let i = 1;i<=12;i++){
      months.push(`${i}`)
    }

    const days= this.generateDays(currentDate)

    return [years, months, days]
  }

  generateDays(currentDate: Date) {
    const m31 = [1, 3, 5, 7, 8, 10, 12]
    const curMonth = currentDate.getMonth() + 1
    let lastDay = 30
    if (curMonth === 2) {
      if (this.isLeapYear(currentDate.getFullYear())) {
        lastDay = 29
      } else {
        lastDay = 28
      }
    } else if (m31.includes(curMonth)) {
      lastDay = 31
    }

    const days: string[] = []

    for (let i = 1; i <= lastDay; i++) {
      days.push(`${i}`)
    }
    return days
  }

  isLeapYear(year: number) {
    let flag = false
    if (year % 4 === 0 && year % 100 !== 0 || year % 400 === 0) {
      flag = true
    }
    return flag
  }

  change(value: string | string[], index: number | number[]) {
    console.log(`change() index : ${index}`)
    const startDate = this.getStartDate()
    const endDate = this.getEndDate()
    const range = this.range
    let date: Date;

    const year = (range[0][(index as number[])[0]])
    const selectedMonth = (index as number[])[1] + 1
    const day = (range[2][(index as number[])[2]])
    date = new Date(`${year}-${selectedMonth}-${day}`);

    if (date > endDate) {
      date = endDate;
    } else if (date < startDate) {
      date = startDate;
    }
    const newDays = this.generateDays(date)
    console.log(`newDays : ${newDays}`)

    if (newDays.length !== this.range[2].length) {
      console.log(`days change....`)
      this.range[2] = [...newDays];

      setTimeout(() => {
        this.range = [...this.range];
      }, 0);
    }
    const month = range[1][date.getMonth()]
    this.selected = [
      range[0].indexOf(String(date.getFullYear())),
      range[1].indexOf(month),
      range[2].indexOf(String(date.getDate())),
    ];
  }

  build() {
    Column() {
      TextPicker({ range: this.range, selected: this.selected })
        .canLoop(false)
        .onChange((value: string | string[], index: number | number[]) => {
          this.change(value, index)
          this.selected = index as number[]
        })
        .height(200)
        .width('100%')
    }.height(270)
  }
}

@Entry
@Component
struct PickerPage {
  @State message: string = 'Hello World';
  private datePickerController: CustomDialogController | null = null

  aboutToAppear(): void {
    this.datePickerController = new CustomDialogController({
      builder: DatePickerDialog(),
      autoCancel: true,
      onWillDismiss: () => {
        this.datePickerController?.close()
      },
      alignment: DialogAlignment.Bottom,
    })
  }

  build() {
    Column() {
      Button('open').onClick(()=>{
        this.datePickerController?.open()
      })
    }
    .height('100%')
    .width('100%')
  }
}