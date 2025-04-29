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

import { MyComponent } from './common/MyComponent';

declare interface sets0 {
  toastInfo?: string
  width?: number | string
  height?: number | string
  widthTwo?: Resource
  heightTwo?: Resource

}

@Entry
@Component
struct CounterExample0_0 {
  @State value: number = 0
  @State widthOne?: number | string = 150
  @State heightOne?: number | string = 100
  @State widthTwo?: Resource = $r('app.float.Length_Resource_150')
  @State heightTwo?: Resource = $r('app.float.Length_Resource_100')
  @State toastInfo?: string = ' '
  @State calcIndex: number = -1
  private index: number = -1
  private lastIndex: number = 0
  private sets: sets0[] = [

    {
      toastInfo: '正常设置',

      width: 150,
      height: 100,

      widthTwo: $r('app.float.Length_Resource_150'),
      heightTwo: $r('app.float.Length_Resource_100')

    },
    {
      toastInfo: '宽高设置负值',

      width: -150,
      height: -100,

      widthTwo: $r('app.float.Length_Resource_minus_150'),
      heightTwo: $r('app.float.Length_Resource_minus_100')

    },
    {
      toastInfo: '宽高设置0',

      width: 0,
      height: 0,

      widthTwo: $r('app.float.Length_Resource_0'),
      heightTwo: $r('app.float.Length_Resource_0')
    },
    {
      toastInfo: '宽高设置大的正常值',

      width: 360,
      height: 100,

      widthTwo: $r('app.float.Length_Resource_360'),
      heightTwo: $r('app.float.Length_Resource_100')

    },
    {
      toastInfo: '宽高设置超大的正常值',

      width: 500,
      height: 100,

      widthTwo: $r('app.float.Length_Resource_500'),
      heightTwo: $r('app.float.Length_Resource_100')

    },

    //宽高百分比 - string(num)
    {
      toastInfo: '宽高设置正常值',

      width: '40%',
      height: '20%',

      widthTwo: $r('app.string.Length_Resource_40percent'),
      heightTwo: $r('app.string.Length_Resource_20percent')

    },
    {
      toastInfo: '宽高设置正常值',

      width: '40',
      height: '20',

      widthTwo: $r('app.string.Length_Resource_40'),
      heightTwo: $r('app.string.Length_Resource_20')

    },
    {
      toastInfo: '宽高设置负值',

      width: '-40%',
      height: '-20%',

      widthTwo: $r('app.string.Length_Resource_minus_40percent'),
      heightTwo: $r('app.string.Length_Resource_minus_20percent')
    },
    {
      toastInfo: '宽高设置负值',

      width: '-40',
      height: '-20',

      widthTwo: $r('app.string.Length_Resource_minus_40'),
      heightTwo: $r('app.string.Length_Resource_minus_20')
    },
    {
      toastInfo: '宽高设置0',

      width: '0%',
      height: '0%',

      widthTwo: $r('app.string.Length_Resource_0percent'),
      heightTwo: $r('app.string.Length_Resource_0percent')

    },
    {
      toastInfo: '宽高设置0',

      width: '0',
      height: '0',

      widthTwo: $r('app.string.Length_Resource_0'),
      heightTwo: $r('app.string.Length_Resource_0')


    },
    {
      toastInfo: '宽高设置大的正常值-百分比',

      width: '98%',
      height: '40%',

      widthTwo: $r('app.string.Length_Resource_98percent'),
      heightTwo: $r('app.string.Length_Resource_40percent')

    },
    {
      toastInfo: '宽高设置大的正常值-数字的字符串和Resource',

      width: '98',
      height: '40',

      widthTwo: $r('app.string.Length_Resource_98'),
      heightTwo: $r('app.string.Length_Resource_40')

    },
    {
      toastInfo: '宽高设置超大正常值',

      width: '120%',
      height: '40%',

      widthTwo: $r('app.string.Length_Resource_120percent'),
      heightTwo: $r('app.string.Length_Resource_40percent')

    },
    {
      toastInfo: '宽高设置超大正常值',

      width: '120',
      height: '40',

      widthTwo: $r('app.string.Length_Resource_120'),
      heightTwo: $r('app.string.Length_Resource_40')
    },
    {
      toastInfo: '宽高设置文本字符串',

      width: '120percent',
      height: '40percent',

      widthTwo: $r('app.string.Length_Resource_120_percent'),
      heightTwo: $r('app.string.Length_Resource_40_percent')
    },
    {
      toastInfo: '宽高设置带单位px的数字字符串',

      width: '120px',
      height: '40px',

      widthTwo: $r('app.string.Length_Resource_120px'),
      heightTwo: $r('app.string.Length_Resource_40px')

    },
    {
      toastInfo: '宽高设置带单位vp的数字字符串',

      width: '120vp',
      height: '40vp',

      widthTwo: $r('app.string.Length_Resource_120vp'),
      heightTwo: $r('app.string.Length_Resource_40vp')

    },
  ]

  private setParam(): void {
    this.toastInfo = this.sets[this.index].toastInfo

    this.widthOne = this.sets[this.index].width
    this.heightOne = this.sets[this.index].height

    this.widthTwo = this.sets[this.index].widthTwo
    this.heightTwo = this.sets[this.index].heightTwo

  }

  build() {

    Column() {
      Text('切换测试参数')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10, top: 5 })

      Row({ space: 2 }) {

        Text(`${this.sets.length}` + '  ')
          .key('paramSets_key')
          .fontSize(9)
          .fontColor(0xCCCCCC)

        MyComponent({
          title: 'Test ++', func: () => {

            this.index++

            if (this.index == this.sets.length) {
              this.index = 0
            }
            this.setParam()
            this.calcIndex = this.index


          }
        })

        MyComponent({
          title: 'Test --', func: () => {

            this.index--

            if (this.index <= -1) {
              this.index = this.sets.length - 1
            }
            this.setParam()
            this.calcIndex = this.index
          }
        })

      }
      .margin({ top: 10 })

      Column() {

        Counter() {
          Text(this.value.toString())
        }

        //通用属性设置
        .width(this.widthOne)
        .height(this.heightOne)

        .margin(10)
        //自有属性设置
        .enableInc(true)
        .enableDec(true)
        .enabled(true)

        //自有事件设置
        .onInc(() => {
          this.value++
        })
        .onDec(() => {
          this.value--
        })

        Counter() {

          Text(this.value.toString())
        }

        //通用属性设置
        .width(this.widthTwo)
        .height(this.heightTwo)

        .margin(10)

        //自有属性设置
        .enableInc(true)
        .enableDec(true)
        .enabled(true)

        //自有事件设置
        .onInc(() => {
          this.value++
        })
        .onDec(() => {
          this.value--
        })

        Text('配置信息显示: ' + ' \n ' +
          '    ' + `${this.calcIndex + 1}` + ': ' + this.toastInfo)
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10, bottom: 5 })

      }
      .width('100%').margin({ top: 10 })
      .borderWidth(0.5).borderColor(Color.Blue)

    }
  }
}