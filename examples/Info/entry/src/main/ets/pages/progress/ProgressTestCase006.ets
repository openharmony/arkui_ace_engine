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

class MyProgressModifier1 implements ContentModifier<ProgressConfiguration> {
  public customNumberArr: (number)[] = []
  public customString: string = ''
  public customClick: boolean = false
  public color: Color = Color.White

  constructor(numberType: (number)[], stringType: string, color: Color) {
    this.customNumberArr = numberType
    this.customString = stringType
    this.color = color
  }

  setOnClick(flag: boolean) {
    this.customClick = flag;
    console.log('ProgressLevel16_customClick: ' + this.customClick);
  }

  applyContent(): WrappedBuilder<[ProgressConfiguration]> {
    return wrapBuilder(progress1)
  }
}

@Builder
function progress1(config: ProgressConfiguration) {
  Column() {
    Row() {
      Path()
        .width('20%')
        .height('20%')
        .commands('M108 0 L141 70 L218 78.3 L162 131 L175 205 L108 170 L41.2 205 L55 131 L1 78 L75 68 L108 0 Z')
        .fill(config.enabled && config.value >= 20 ? (config.contentModifier as MyProgressModifier1).color :
        Color.White)
        .stroke(Color.Black)
        .strokeWidth(2)
      Path()
        .width('20%')
        .height('20%')
        .commands('M108 0 L141 70 L218 78.3 L162 131 L175 205 L108 170 L41.2 205 L55 131 L1 78 L75 68 L108 0 Z')
        .fill(config.enabled && config.value >= 50 ? (config.contentModifier as MyProgressModifier1).color :
        Color.White)
        .stroke(Color.Black)
        .strokeWidth(2)
      Path()
        .width('20%')
        .height('20%')
        .commands('M108 0 L141 70 L218 78.3 L162 131 L175 205 L108 170 L41.2 205 L55 131 L1 78 L75 68 L108 0 Z')
        .fill(config.enabled && config.value >= 100 ? (config.contentModifier as MyProgressModifier1).color :
        Color.White)
        .stroke(Color.Black)
        .strokeWidth(2)
      if (config.total >= 150) {
        Path()
          .width('20%')
          .height('20%')
          .commands('M108 0 L141 70 L218 78.3 L162 131 L175 205 L108 170 L41.2 205 L55 131 L1 78 L75 68 L108 0 Z')
          .fill(config.enabled && config.value >= 150 ? (config.contentModifier as MyProgressModifier1).color :
          Color.White)
          .stroke(Color.Black)
          .strokeWidth(2)
      }
    }

    Text(`value: ${config.value}, total: ${config.total}, enable: ${config.enabled}, 
      customNumberArr: ${JSON.stringify((config.contentModifier as MyProgressModifier1).customNumberArr)},
      customString: ${JSON.stringify((config.contentModifier as MyProgressModifier1).customString)}, 
      customClick: ${JSON.stringify((config.contentModifier as MyProgressModifier1).customClick)},
      color: ${JSON.stringify((config.contentModifier as MyProgressModifier1).color)}`)
      .fontSize(9)
      .fontColor(0xCCCCCC)
      .width('80%')
      .margin({ top: 50 })
  }
  .backgroundColor('#E0FFFF')
  .width(450)
  .height(200)
}

class MyProgressModifier2 implements ContentModifier<ProgressConfiguration> {
  applyContent(): WrappedBuilder<[ProgressConfiguration]> {
    return wrapBuilder(progress2)
  }
}

// contentModifier设置了小于Progress的宽高
@Builder
function progress2(config: ProgressConfiguration) {
  Column() {
    Row({ space: 2 }) {
      Checkbox({ name: 'checkbox1', group: 'checkboxGroup' })
        .select(config.enabled && config.value >= 20 ? true : false)
        .selectedColor(0xed6f21)
        .shape(CheckBoxShape.CIRCLE)
      Checkbox({ name: 'checkbox2', group: 'checkboxGroup' })
        .select(config.enabled && config.value >= 50 ? true : false)
        .selectedColor(0xed6f21)
        .shape(CheckBoxShape.CIRCLE)
      Checkbox({ name: 'checkbox3', group: 'checkboxGroup' })
        .select(config.enabled && config.value >= 100 ? true : false)
        .selectedColor(0xed6f21)
        .shape(CheckBoxShape.CIRCLE)
      if (config.total >= 150) {
        Checkbox({ name: 'checkbox3', group: 'checkboxGroup' })
          .select(config.enabled && config.value >= 150 ? true : false)
          .selectedColor(0xed6f21)
          .shape(CheckBoxShape.CIRCLE)
      }
    }

    Text(`value: ${config.value}, total: ${config.total}, enable: ${config.enabled}`)
      .fontSize(9)
      .fontColor(Color.Black)
      .width('80%')
  }
  .backgroundColor('#E0FFFF')
  .width(300)
  .height(100)
}

// 空的contentModifier
class MyProgressModifier3 implements ContentModifier<ProgressConfiguration> {
  applyContent(): WrappedBuilder<[ProgressConfiguration]> {
    return wrapBuilder(progress3)
  }
}

@Builder
function progress3(config: ProgressConfiguration) {
  Column() {
  }
  .backgroundColor('#E0FFFF')
}

class MyProgressModifier4 implements ContentModifier<ProgressConfiguration> {
  public color: Color = Color.White

  constructor(color: Color) {
    this.color = color
  }

  applyContent(): WrappedBuilder<[ProgressConfiguration]> {
    return wrapBuilder(progress4)
  }
}

// contentModifier不设置宽高
@Builder
function progress4(config: ProgressConfiguration) {
  Column() {
    Row({ space: 40 }) {
      Path()
        .width(30)
        .height(30)
        .commands('M108 0 L141 70 L218 78.3 L162 131 L175 205 L108 170 L41.2 205 L55 131 L1 78 L75 68 L108 0 Z')
        .fill(config.enabled && config.value >= 20 ? (config.contentModifier as MyProgressModifier4).color :
        Color.White)
        .stroke(Color.Black)
        .strokeWidth(2)
      Path()
        .width(30)
        .height(30)
        .commands('M108 0 L141 70 L218 78.3 L162 131 L175 205 L108 170 L41.2 205 L55 131 L1 78 L75 68 L108 0 Z')
        .fill(config.enabled && config.value >= 50 ? (config.contentModifier as MyProgressModifier4).color :
        Color.White)
        .stroke(Color.Black)
        .strokeWidth(2)
      Path()
        .width(30)
        .height(30)
        .commands('M108 0 L141 70 L218 78.3 L162 131 L175 205 L108 170 L41.2 205 L55 131 L1 78 L75 68 L108 0 Z')
        .fill(config.enabled && config.value >= 100 ? (config.contentModifier as MyProgressModifier4).color :
        Color.White)
        .stroke(Color.Black)
        .strokeWidth(2)
      if (config.total >= 150) {
        Path()
          .width(30)
          .height(30)
          .commands('M108 0 L141 70 L218 78.3 L162 131 L175 205 L108 170 L41.2 205 L55 131 L1 78 L75 68 L108 0 Z')
          .fill(config.enabled && config.value >= 150 ? (config.contentModifier as MyProgressModifier4).color :
          Color.White)
          .stroke(Color.Black)
          .strokeWidth(2)
      }
    }

    Text(`value: ${config.value}, total: ${config.total}, enable: ${config.enabled}, color: ${JSON.stringify((config.contentModifier as MyProgressModifier4).color)}`)
      .fontSize(9)
      .fontColor(Color.Black)
      .width('80%')
      .margin({ top: 50 })
  }
  .backgroundColor('#E0FFFF')
}

@Entry
@Component
struct ProgressLevel1_6 {
  @State flag: boolean = false;
  @State valueIndex: number = 0;
  @State valueList: (number | undefined | null)[] = [0, 20, 50, 100, 150, -2, -1.5, 25.5, undefined, null];
  @State totalIndex: number = 0;
  @State totalList: (number | undefined | null)[] = [0, 20, 50, 80, 100, 150, -2, -1.5, 25.5, undefined, null];
  @State enableIndex: number = 0;
  @State enableList: (boolean | undefined | null)[] = [true, false, undefined, null];
  @State builderIndex: number = 0;
  @State builderList: (ContentModifier<ProgressConfiguration> | undefined | null)[] = [
    null,
    new MyProgressModifier1([50, 100], 'This is Builder Test', Color.Red), // contentModifier设置了大于Progress的宽高
    undefined,
    new MyProgressModifier2(), // contentModifier设置了小于Progress的宽高
    new MyProgressModifier3(), // 空白
    new MyProgressModifier4(Color.Pink)// contentModifier不设置宽高
  ];
  @State modifier1: MyProgressModifier1 = new MyProgressModifier1([50, 100], 'This is Builder Test', Color.Red);
  @State typeIndex: number = 0;
  private typeList: (ProgressType | undefined | null)[] = [
    ProgressType.Linear, ProgressType.Ring, undefined, ProgressType.ScaleRing, ProgressType.Eclipse,
    ProgressType.Capsule, null
  ];
  @State btnHeight: number = 30;
  @State btnMargin: number = 2;
  @State hideText: boolean = false

  build() {
    Scroll() {
      Column() {
        Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Center }) {
          Button('contentModifier++')
            .height(this.btnHeight)
            .margin(this.btnMargin)
            .onClick(() => {
              this.builderIndex++;
              if (this.builderIndex > this.builderList.length - 1) {
                this.builderIndex = 0;
              }
            })

          Button('value++')
            .height(this.btnHeight)
            .margin(this.btnMargin)
            .onClick(() => {
              this.valueIndex++;
              if (this.valueIndex > this.valueList.length - 1) {
                this.valueIndex = 0;
              }
            })

          Button('total++')
            .height(this.btnHeight)
            .margin(this.btnMargin)
            .onClick(() => {
              this.totalIndex++;
              if (this.totalIndex > this.totalList.length - 1) {
                this.totalIndex = 0;
              }
            })

          Button('type++')
            .height(this.btnHeight)
            .margin(this.btnMargin)
            .onClick(() => {
              this.typeIndex++;
              if (this.typeIndex > this.typeList.length - 1) {
                this.typeIndex = 0;
              }
            })

          Button('enable++')
            .height(this.btnHeight)
            .margin(this.btnMargin)
            .onClick(() => {
              this.enableIndex++;
              if (this.enableIndex > this.enableList.length - 1) {
                this.enableIndex = 0;
              }
            })
          Button('hideText: ' + this.hideText)
            .height(this.btnHeight)
            .margin(this.btnMargin)
            .onClick(() => {
              this.hideText = !this.hideText
            })
            .key('hideText')
        }

        Text(`contentModifier=${this.builderList[this.builderIndex]}, Type=${this.typeList[this.typeIndex]}, value=${this.valueList[this.valueIndex]}, total=${this.totalList[this.totalIndex]}, enabled=${this.enableList[this.enableIndex]}`)
          .fontSize(9)
          .fontColor(Color.Black)
          .width('95%')
          .margin({ top: 5, bottom: 5 })

        Column() {
          Text('1.不设置contentModifier，设置value属性值为30，参数value、total、type动态切换')
            .fontSize(12)
            .fontColor(0xCCCCCC)
            .width('95%')
            .margin({ bottom: 5 })
            .visibility(this.hideText ? Visibility.None : Visibility.Visible)
          Progress({
            value: this.valueList[this.valueIndex],
            total: this.totalList[this.totalIndex],
            type: this.typeList[this.typeIndex]
          })
            .value(30)
            .enabled(this.enableList[this.enableIndex])
            .height(50)
            .width(350)

          // 终端可以打印onClick和setOnClick的日志，但是页面上的customClick不会被修改。目前判断是对象解析导致的问题
          Text('2.设置contentModifier，参数value、total、type，enabled、contentModifier动态切换，自定义方法测试')
            .fontSize(12)
            .fontColor(0xCCCCCC)
            .width('95%')
            .margin({ top: 10, bottom: 5 })
            .visibility(this.hideText ? Visibility.None : Visibility.Visible)
          Progress({
            value: this.valueList[this.valueIndex],
            total: this.totalList[this.totalIndex],
            type: this.typeList[this.typeIndex]
          })
            .contentModifier(this.builderList[this.builderIndex])
            .enabled(this.enableList[this.enableIndex])// .height(50)
              // .width(50)
            .height(140)
            .width(350)
            .onClick(() => {
              this.flag = !this.flag;
              if (this.builderIndex === 1) {
                (this.builderList[this.builderIndex] as MyProgressModifier1).setOnClick(this.flag);
              }
              console.log('ProgressLevel16_flag_1: ' + this.flag)
            })

          Text('3.Progress同时设置value参数和value属性，value属性值动态变化，不设置Progress的宽高')
            .fontSize(12)
            .fontColor(0xCCCCCC)
            .width('95%')
            .margin({ top: 10, bottom: 5 })
            .visibility(this.hideText ? Visibility.None : Visibility.Visible)
          Column() {
            Progress({
              value: 80,
              total: this.totalList[this.totalIndex],
              type: this.typeList[this.typeIndex]
            })
              .value(this.valueList[this.valueIndex])
              .contentModifier(this.builderList[this.builderIndex])
              .enabled(this.enableList[this.enableIndex])
              .color(Color.Green)
              .backgroundColor(Color.Blue)
          }
          .height(180)

          Text('4.不设置enable参数，progress本身设置value、color、backgroundColor、style（包含LOADING状态）')
            .fontSize(12)
            .fontColor(0xCCCCCC)
            .width('95%')
            .margin({ top: 10, bottom: 5 })
            .visibility(this.hideText ? Visibility.None : Visibility.Visible)
          Progress({
            value: this.valueList[this.valueIndex],
            total: 50,
            type: ProgressType.Ring
          })
            .contentModifier(this.builderList[this.builderIndex])
            .value(30)
            .color(Color.Green)
            .backgroundColor('#90EE90')
            .style({
              strokeWidth: 8,
              scaleCount: 100,
              scaleWidth: 3,
              enableSmoothEffect: true,
              status: ProgressStatus.LOADING
            })
            .height(150)
            .width(350)
            .key('progress03')
          // 终端可以打印onClick和setOnClick的日志，页面上的customClick也会被修改
          Text('5.自定义方法测试')
            .fontSize(12)
            .fontColor(0xCCCCCC)
            .width('95%')
            .margin({ top: 60, bottom: 5 })
            .visibility(this.hideText ? Visibility.None : Visibility.Visible)
          Progress({
            value: 80,
            total: this.totalList[this.totalIndex],
            type: this.typeList[this.typeIndex]
          })
            .value(this.valueList[this.valueIndex])
            .contentModifier(this.modifier1)
            .enabled(this.enableList[this.enableIndex])
            .color(Color.Green)
            .backgroundColor(Color.Blue)
            .height(150)
            .width(350)
            .onClick(() => {
              this.flag = !this.flag;
              this.modifier1.setOnClick(this.flag)
              console.log('ProgressLevel16_flag_2: ' + this.flag)
            })
            .key('progress04')
        }
        .key('testArea')
      }
    }
    .width('100%')
    .height('100%')
  }
}