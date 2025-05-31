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

import { Model1 } from '../../../common/SelectData';
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';
import { ThemeControl } from '@kit.ArkUI';

interface objectSample {
  mValue1?: ResourceStr | undefined
  mIcon1?: ResourceStr | undefined
  mValue2?: ResourceStr | undefined
  mIcon2?: ResourceStr | undefined
  mValue3?: ResourceStr | undefined
  mIcon3?: ResourceStr | undefined
  mValue4?: ResourceStr | undefined
  mIcon4?: ResourceStr | undefined
  mValue5?: ResourceStr | undefined
  mIcon5?: ResourceStr | undefined
  mSymbolIcon1?: SymbolGlyphModifier | undefined
  mSymbolIcon2?: SymbolGlyphModifier | undefined
  mSymbolIcon3?: SymbolGlyphModifier | undefined
  mSymbolIcon4?: SymbolGlyphModifier | undefined
  mSymbolIcon5?: SymbolGlyphModifier | undefined
}

ThemeControl.setDefaultTheme(undefined);

@Builder
export function SelectLevel00Builder(name: string, param: Object) {
  SelectLevel0_0()
}

@Entry
@Component
struct SelectLevel0_0 {
  pathStack: NavPathStack = new NavPathStack()
  @State model: Model1 = new Model1()
  @State index: number = 0
  @State info: string | undefined = undefined
  @State show: boolean = false
  @State testCase: Array<objectSample> = [
    {
      mValue1: '',
      mIcon1: '',
      mSymbolIcon1: undefined,

      mValue2: '这是选项AA',
      mIcon2: '/pages/picture/ic_public_favor.svg',
      mSymbolIcon2: undefined,

      mValue3: '这是选项BB',
      mIcon3: '/pages/picture/gif.gif',
      mSymbolIcon3: undefined,

      mValue4: '这是选项CC',
      mIcon4: '/pages/picture/star-2-21.png',
      mSymbolIcon4: undefined,

      mValue5: '这是选项DD',
      mIcon5: 'data:image/bmp;base64,Qk1qLAAAAAAAAIoAAAB8AAAATgAAACQAAAABACAAAwAAAOArAADDDgAAww4AAAAAAAAAAAAAAAD/AAD/AAD/AAAAAAAA/0JHUnOAwvUoYLgeFSCF6wFAMzMTgGZmJkBmZgagmZkJPArXAyRcjzIAAAAAAAAAAAAAAAAEAAAAAAAAAAAAAAAAAAAAUNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/UNCS/1DQkv9Q0JL/',
      mSymbolIcon5: undefined,
    },
    {
      //真机上该选项存在，内容为空
      mValue1: $r('app.string.Empty_string'),
      mIcon1: $r('app.media.app_icon'),
      mSymbolIcon1: new SymbolGlyphModifier($r('sys.symbol.ohos_wifi')),

      mValue2: $r('app.string.app_name'),
      mIcon2: $r('app.media.app_icon'),
      mSymbolIcon2: new SymbolGlyphModifier($r('sys.symbol.ohos_wifi')),

      mValue3: $r('app.string.Long_string'),
      mIcon3: $r('app.media.app_icon'),
      mSymbolIcon3: new SymbolGlyphModifier($r('sys.symbol.ohos_wifi')),

      mValue5: $r('app.float.float_1'),
      mIcon5: $r('app.media.app_icon'),
      mSymbolIcon5: new SymbolGlyphModifier($r('sys.symbol.ohos_wifi')),
    },
    {
      //用例生效
      mValue1: 'aaa',
      mIcon1: undefined,
      mSymbolIcon1: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),

      mValue2: 'aaa',
      mIcon2: $r('app.media.app_icon'),
      mSymbolIcon2: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),

      mValue3: 'aaa',
      mIcon3: $r('app.media.app_icon'),
      mSymbolIcon3: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),

      mValue4: 'aaa',
      mIcon4: $r('app.media.app_icon'),
      mSymbolIcon4: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),

      mValue5: 'aaa',
      mIcon5: $r('app.media.app_icon'),
      mSymbolIcon5: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),
    },
    {
      mValue1: $r('app.media.app_icon'),
      mIcon1: $r('app.media.app_icon'),

      mValue2: 'aaa',
      mIcon2: $r('app.media.app_icon'),

      mValue3: 'aaa',
      mIcon3: $r('app.media.app_icon'),

      mValue4: 'aaa',
      mIcon4: $r('app.media.app_icon'),

      mValue5: 'aaa',
      mIcon5: $r('app.media.app_icon'),
    },

    {
      mValue1: undefined,
      mIcon1: $r('app.media.app_icon'),

      mValue2: 'aaa',
      mIcon2: $r('app.media.app_icon'),

      mValue3: 'aaa',
      mIcon3: $r('app.media.app_icon'),

      mValue4: 'aaa',
      mIcon4: $r('app.media.app_icon'),

      mValue5: 'aaa',
      mIcon5: $r('app.media.app_icon'),
    },
  ]
  @State selectValue: string = ''
  @State connectType1: number = 0
  @State connectType2: number = 0
  @State connectType3: number = 0
  @State selectOption1: SelectOption[] = []
  @State selectOption2: SelectOption[] = [{ value: '' }]
  @State selectOption3: SelectOption[] = []

  private setParam(): void {
    // 1. 参数赋值
    this.model.mValue1 = this.testCase[this.index].mValue1
    this.model.mIcon1 = this.testCase[this.index].mIcon1
    this.model.mValue2 = this.testCase[this.index].mValue2
    this.model.mIcon2 = this.testCase[this.index].mIcon2
    this.model.mValue3 = this.testCase[this.index].mValue3
    this.model.mIcon3 = this.testCase[this.index].mIcon3
    this.model.mValue4 = this.testCase[this.index].mValue4
    this.model.mIcon4 = this.testCase[this.index].mIcon4
    this.model.mValue5 = this.testCase[this.index].mValue5
    this.model.mIcon5 = this.testCase[this.index].mIcon5
    this.model.mSymbolIcon1 = this.testCase[this.index].mSymbolIcon1
    this.model.mSymbolIcon2 = this.testCase[this.index].mSymbolIcon2
    this.model.mSymbolIcon3 = this.testCase[this.index].mSymbolIcon3
    this.model.mSymbolIcon4 = this.testCase[this.index].mSymbolIcon4
    this.model.mSymbolIcon5 = this.testCase[this.index].mSymbolIcon5

    // 2. 参数打印
    this.info = 'Total: ' + this.testCase.length + ', CaseNumber: ' + this.index +
      '\nmValue1: ' + this.testCase[this.index].mValue1 + '\nmIcon1: ' + this.testCase[this.index].mIcon1 +
      '\nmValue2: ' + this.testCase[this.index].mValue2 + '\nmIcon2: ' + this.testCase[this.index].mIcon2 +
      '\nmValue3: ' + this.testCase[this.index].mValue3 + '\nmIcon3: ' + this.testCase[this.index].mIcon3 +
      '\nmValue4: ' + this.testCase[this.index].mValue4 + '\nmIcon4: ' + this.testCase[this.index].mIcon4 +
      '\nmValue5: ' + this.testCase[this.index].mValue5 + '\nmIcon5: ' + this.testCase[this.index].mIcon5 +
      '\nmSymbolIcon1: ' + this.testCase[this.index].mSymbolIcon1 + '\nmSymbolIcon1: ' +
    this.testCase[this.index].mSymbolIcon1 +
      '\nmSymbolIcon2: ' + this.testCase[this.index].mSymbolIcon2 + '\nmSymbolIcon2: ' +
    this.testCase[this.index].mSymbolIcon2 +
      '\nmSymbolIcon3: ' + this.testCase[this.index].mSymbolIcon3 + '\nmSymbolIcon3: ' +
    this.testCase[this.index].mSymbolIcon3 +
      '\nmSymbolIcon4: ' + this.testCase[this.index].mSymbolIcon4 + '\nmSymbolIcon4: ' +
    this.testCase[this.index].mSymbolIcon4 +
      '\nmSymbolIcon5: ' + this.testCase[this.index].mSymbolIcon5 + '\nmSymbolIcon5: ' +
    this.testCase[this.index].mSymbolIcon5
  }

  aboutToAppear(): void {
    this.setParam()
    this.selectOption1 =
      [{ value: 'TCP' }, { value: 'UDP' }, { value: 'Bluetooth' }, { value: 'USB' }, { value: 'MQTT' }]

    setTimeout(() => {
      this.selectOption2 =
        [{ value: 'TCP' }, { value: 'UDP' }, { value: 'Bluetooth' }, { value: 'USB' }, { value: 'MQTT' }]

      this.selectOption3 =
        [{ value: 'TCP' }, { value: 'UDP' }, { value: 'Bluetooth' }, { value: 'USB' }, { value: 'MQTT' }]
    }, 4000)
  }

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Divider()
        Text('2.切换参数，显示参数=' + this.show)
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .focusable(false)
          .onClick(() => {
            this.show = !this.show
          })

        Row({ space: 2 }) {
          Text(`${this.index + 1}` + `/`)
            .focusable(false)
          Text(`${this.testCase.length}`).key('num')
            .focusable(false)
          Text('Test++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .focusable(false)
            .onClick(() => {
              // 控制循环
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
            .focusable(false)
            .onClick(() => {
              // 控制循环
              this.index--
              if (this.index == -1) {
                this.index = this.testCase.length - 1
              }
              this.setParam()
            })
        }

        if (this.show) {
          Text(this.info)
            .focusable(false)
        }

        Select([{ value: this.model.mValue1!, icon: this.model.mIcon1, symbolIcon: this.model.mSymbolIcon1 },
          { value: this.model.mValue2!, icon: this.model.mIcon2, symbolIcon: this.model.mSymbolIcon2 },
          { value: this.model.mValue3!, icon: this.model.mIcon3, symbolIcon: this.model.mSymbolIcon3 },
          { value: this.model.mValue4!, icon: this.model.mIcon4, symbolIcon: this.model.mSymbolIcon4 },
          { value: this.model.mValue5!, icon: this.model.mIcon5, symbolIcon: this.model.mSymbolIcon5 }
        ])
          .selected(1)
          .value('接口参数测试')
          .key('0Select1')

        Divider().height(20)
        Text('正常显示，选项在显示前赋值')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .focusable(false)
        Select(this.selectOption1)
          .selected(this.connectType1)
          .value(this.selectOption1[this.connectType1].value)
          .font({ size: 16 })
          .fontColor($r('sys.color.font_primary'))
          .selectedOptionFont({ size: 16 })
          .optionFont({ size: 16 })
          .optionWidth(OptionWidthMode.FIT_TRIGGER)
          .optionHeight(300)
          .borderRadius(10)
          .onSelect((index: number) => {
            this.connectType1 = index
          })
          .width('90%')
          .key('0Select2')

        Text('正常显示，选项在显示前赋值[{ value: \'\' }]，后在aboutToAppear中延迟2秒赋值')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .focusable(false)
        Select(this.selectOption2)
          .selected(this.connectType2)
          .value(this.selectOption2[this.connectType2].value)
          .font({ size: 16 })
          .fontColor($r('sys.color.font_primary'))
          .selectedOptionFont({ size: 16 })
          .optionFont({ size: 16 })
          .optionWidth(OptionWidthMode.FIT_TRIGGER)
          .optionHeight(300)
          .borderRadius(10)
          .onSelect((index: number) => {
            this.connectType2 = index
          })
          .width('90%')
          .key('0Select3')

        Text('存在Bug显示，选项在显示前赋值[]，后在aboutToAppear中延迟2秒赋值')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .focusable(false)
        Select(this.selectOption3)
          .selected(this.connectType3)
          .value(this.selectValue)
          .font({ size: 16 })
          .fontColor($r('sys.color.font_primary'))
          .selectedOptionFont({ size: 16 })
          .optionFont({ size: 16 })
          .optionWidth(OptionWidthMode.FIT_TRIGGER)
          .optionHeight(300)
          .borderRadius(10)
          .onSelect((index: number, text?: string | undefined) => {
            this.connectType3 = index
            if (text != undefined) {
              this.selectValue = text
            }
          })
          .width('90%')
          .key('0Select4')

        Text('optionFont单独设置，选中项文字与非选中项大小一致')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .focusable(false)
        Select([{ value: '菜单1' },
          { value: '菜单2' },
          { value: '菜单3' },
          { value: 'oa+ jila Ltt ojrljlt' }])
          .value('默认菜单')
          .width('90%')
          .selected(2)
          .optionFont({ size: 20 })
          .onSelect((index: number, text?: string | undefined) => {
            console.info('lhg-select:' + index)
          })
          .key('0Select5')
      }.width('100%')
    }
    .title('SelectLevel00')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}