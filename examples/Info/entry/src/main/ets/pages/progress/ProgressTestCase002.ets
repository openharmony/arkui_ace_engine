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

interface TestCaseLevel11 {
  value1?: number
  total?: number
  value2?: number
  color?: ResourceColor | LinearGradient
  mbackgroundColor?: ResourceColor
  strokeWidth?: Length
  scaleCount?: number
  scaleWidth?: Length
  enableSmoothEffect?: boolean
}

@Entry
@Component
struct ProgressLevel1_1 {
  private index: number = -1
  @State info?: string = undefined
  @State show: boolean = false
  @State value1?: number = undefined
  @State total?: number = undefined
  @State value2?: number = undefined
  @State color?: ResourceColor | LinearGradient = undefined
  @State mbackgroundColor?: ResourceColor = undefined
  @State strokeWidth?: Length = undefined
  @State scaleCount?: number = undefined
  @State scaleWidth?: Length = undefined
  @State enableSmoothEffect?: boolean = undefined
  @State direction1?: Direction | null = undefined
  private testCase: Array<TestCaseLevel11> = [
    {
      value1: -20,
      total: -20,
      value2: -10,
      color: Color.Red,
      mbackgroundColor: Color.Brown,
      strokeWidth: -10,
      scaleCount: 5.5,
      scaleWidth: -100,
      enableSmoothEffect: true,
    },
    {
      value1: 0,
      total: 0,
      value2: 0,
      color: Color.Red,
      mbackgroundColor: Color.Green,
      strokeWidth: 0,
      scaleCount: 90,
      scaleWidth: 0,
      enableSmoothEffect: true,
    },
    {
      value1: 20,
      total: 80,
      value2: 10,
      color: 0xffa500,
      mbackgroundColor: 0x008000,
      strokeWidth: 10,
      scaleCount: 1,
      scaleWidth: 20,
      enableSmoothEffect: true,
    },
    {
      value1: 20,
      total: 80,
      value2: 50,
      color: Color.Red,
      mbackgroundColor: Color.Green,
      strokeWidth: 10,
      scaleCount: 2,
      scaleWidth: 20,
      enableSmoothEffect: true,
    },
    {
      value1: 120,
      total: 100,
      value2: 120,
      color: '#008000',
      mbackgroundColor: '#ffff00',
      strokeWidth: '50px',
      scaleCount: -100,
      scaleWidth: '10px',
      enableSmoothEffect: false,
    },
    {
      value1: 20,
      total: 100,
      value2: 30,
      color: 'rgb(255, 0, 0)',
      mbackgroundColor: 'rgb(255, 200, 255)',
      strokeWidth: '30%',
      scaleCount: 0,
      scaleWidth: '30%',
      enableSmoothEffect: true,
    },
    {
      value1: -20,
      total: 100,
      value2: 98,
      color: $r('app.color.Orange'),
      mbackgroundColor: $r('app.color.Blue'),
      strokeWidth: $r('app.string.number120'),
      scaleCount: 80,
      scaleWidth: $r('app.string.number1'),
      enableSmoothEffect: true,
    },
    {
      value1: 20,
      total: 100,
      value2: 50,
      color: new LinearGradient([{ color: Color.Orange, offset: -0.3 }, { color: Color.Green, offset: 0.5 }, {
        color: Color.Red,
        offset: 2
      }]),
      mbackgroundColor: undefined,
      strokeWidth: 60,
      scaleCount: 60,
      scaleWidth: 2,
      enableSmoothEffect: true,
    },
    {
      value1: 20,
      total: 100,
      value2: 20,
      color: '',
      mbackgroundColor: '',
      strokeWidth: 60,
      scaleCount: 60,
      scaleWidth: 2,
      enableSmoothEffect: true,
    },
    {
      value1: undefined,
      total: undefined,
      value2: undefined,
      color: undefined,
      mbackgroundColor: undefined,
      strokeWidth: undefined,
      scaleCount: undefined,
      scaleWidth: undefined,
      enableSmoothEffect: undefined,
    }
  ]

  private setInfo(): void {
    this.info = 'Total: ' + this.testCase.length + ', CaseNumber: ' + this.index +
      '\nvalue1: ' + this.value1 + '\ntotal: ' + this.total + '\nvalue2: ' + this.testCase[this.index].value2 +
      '\ncolor: ' + this.testCase[this.index].color + '\nmbackgroundColor: ' +
    this.testCase[this.index].mbackgroundColor +
      '\nstrokeWidth: ' + this.testCase[this.index].strokeWidth + '\nscaleCount: ' +
    this.testCase[this.index].scaleCount +
      '\nscaleWidth: ' + this.testCase[this.index].scaleWidth + '\nenableSmoothEffect: ' +
    this.testCase[this.index].enableSmoothEffect
  }

  private setParam(): void {
    this.value1 = this.testCase[this.index].value1
    this.total = this.testCase[this.index].total
    this.value2 = this.testCase[this.index].value2
    this.color = this.testCase[this.index].color
    this.mbackgroundColor = this.testCase[this.index].mbackgroundColor
    this.strokeWidth = this.testCase[this.index].strokeWidth
    this.scaleCount = this.testCase[this.index].scaleCount
    this.scaleWidth = this.testCase[this.index].scaleWidth
    this.enableSmoothEffect = this.testCase[this.index].enableSmoothEffect

    this.setInfo()
  }

  build() {
    Scroll() {
      Column() {
        Column({ space: 8 }) {
          Text('No type Progress .width(200).height(50)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .height(this.show ? 'auto' : 0)
          Progress({ value: this.value1, total: this.total })
            .width(200)
            .height(50)
            .value(this.value2)
            .color(this.color)
            .backgroundColor(this.mbackgroundColor)
            .style({
              strokeWidth: this.strokeWidth,
              scaleCount: this.scaleCount,
              scaleWidth: this.scaleWidth,
              enableSmoothEffect: this.enableSmoothEffect,
            })
            .direction(this.direction1)

          Text('undefined Progress .width(200)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .height(this.show ? 'auto' : 0)
          Progress({ value: this.value1, total: this.total, type: undefined })
            .width(200)
            .value(this.value2)
            .color(this.color)
            .backgroundColor(this.mbackgroundColor)
            .style({
              strokeWidth: this.strokeWidth,
              scaleCount: this.scaleCount,
              scaleWidth: this.scaleWidth,
              enableSmoothEffect: this.enableSmoothEffect,
            })
            .direction(this.direction1)

          Text('Linear Progress .height(50)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('90%')
            .height(this.show ? 'auto' : 0)
          Progress({ value: this.value1, total: this.total, type: ProgressType.Linear })
            .height(50)
            .value(this.value2)
            .color(this.color)
            .backgroundColor(this.mbackgroundColor)
            .style({
              strokeWidth: this.strokeWidth,
              scaleCount: this.scaleCount,
              scaleWidth: this.scaleWidth,
              enableSmoothEffect: this.enableSmoothEffect,
            })
            .direction(this.direction1)

          Text('Ring Progress width(100)').fontSize(9).fontColor(0xCCCCCC).width('90%').height(this.show ? 'auto' : 0)
          Progress({ value: this.value1, total: this.total, type: ProgressType.Ring })
            .width(100)
            .value(this.value2)
            .color(this.color)
            .backgroundColor(this.mbackgroundColor)
            .style({
              strokeWidth: this.strokeWidth,
              scaleCount: this.scaleCount,
              scaleWidth: this.scaleWidth,
              enableSmoothEffect: this.enableSmoothEffect,
            })
            .direction(this.direction1)

          Text('Eclipse Progress width(100)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('90%')
            .height(this.show ? 'auto' : 0)
          Progress({ value: this.value1, total: this.total, type: ProgressType.Eclipse })
            .width(100)
            .value(this.value2)
            .color(this.color)
            .backgroundColor(this.mbackgroundColor)
            .style({
              strokeWidth: this.strokeWidth,
              scaleCount: this.scaleCount,
              scaleWidth: this.scaleWidth,
              enableSmoothEffect: this.enableSmoothEffect,
            })
            .direction(this.direction1)

          Text('ScaleRing Progress width(100)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('90%')
            .height(this.show ? 'auto' : 0)
          Progress({ value: this.value1, total: this.total, type: ProgressType.ScaleRing })
            .width(100)
            .value(this.value2)
            .color(this.color)
            .backgroundColor(this.mbackgroundColor)
            .style({
              strokeWidth: this.strokeWidth,
              scaleCount: this.scaleCount,
              scaleWidth: this.scaleWidth,
              enableSmoothEffect: this.enableSmoothEffect,
            })
            .direction(this.direction1)

          Text('Capsule Progress .width(200).height(100)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('90%')
            .height(this.show ? 'auto' : 0)
          Progress({ value: this.value1, total: this.total, type: ProgressType.Capsule })
            .width(200)
            .height(100)
            .value(this.value2)
            .color(this.color)
            .backgroundColor(this.mbackgroundColor)
            .style({
              strokeWidth: this.strokeWidth,
              scaleCount: this.scaleCount,
              scaleWidth: this.scaleWidth,
              enableSmoothEffect: this.enableSmoothEffect,
            })
            .direction(this.direction1)
        }
        .key('testArea')
        .height('85%')
        Text('2.切换参数，显示参数=' + this.show)
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .onClick(() => {
            this.show = !this.show
          })
          .key('isShow')
        Row({ space: 2 }) {
          Text(`${this.testCase.length}`).key('num')
          Text('Test++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.index++
              if (this.index == this.testCase.length) {
                this.index = 0
              }
              this.setParam()
            })
          Text('Test--')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.index--
              if (this.index == -1) {
                this.index = this.testCase.length - 1
              }
              this.setParam()
            })
        }
        Text('Direction：' + this.direction1).fontSize(9).fontColor(0xCCCCCC).width('100%')
        Row({ space: 2 }) {
          Button('Ltr').fontSize(8).onClick(() => {
            this.direction1 = Direction.Ltr
          })
          Button('Rtl').fontSize(8).onClick(() => {
            this.direction1 = Direction.Rtl
          })
          Button('Auto').fontSize(8).onClick(() => {
            this.direction1 = Direction.Auto
          })
          Button('null').fontSize(8).onClick(() => {
            this.direction1 = null
          })
        }
        if (this.show) {
          Text(this.info).fontSize(13)
        }
      }
      .width('100%')
    }.scrollBar(BarState.Off)
  }
}