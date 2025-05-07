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

import { MyComponent } from './MyComponent';

declare interface borderInterface {
  minWidth?: number | string
  maxWidth?: number | string
  minHeight?: number | string
  maxHeight?: number | string
}

declare interface sizeInterface {
  width?: number | string | Resource
  height?: number | string | Resource
}

declare interface markAnchorItem {
  x?: string | number
  y?: string | number
}


declare interface sets1 {
  toastInfo?: string
  size?: sizeInterface
  sizeOne?: sizeInterface
  position?: markAnchorItem

}

@Entry
@Component
struct CounterExample0_1 {
  @State value: number = 0
  @State sizeOne?: sizeInterface = { width: 150, height: 100 }
  @State sizeTwo?: sizeInterface =
    { width: $r('app.float.Length_Resource_150'), height: $r('app.float.Length_Resource_100') }
  @State constraintSize_3: borderInterface = {

    minWidth: 0,
    maxWidth: Infinity,
    minHeight: 0,
    maxHeight: Infinity
  }
  @State aspectRatioIndex?: number = undefined
  //内外边距
  @State paddingIndex?: Padding = undefined
  @State marginIndex?: Margin = undefined
  //@State positionIndex: Position = undefined


  @State toastInfo?: string = ' '
  @State calcIndex: number = -1
  private index: number = -1
  private lastIndex: number = 0
  private sets: sets1[] = [

    {
      toastInfo: '正常设置',

      size: {
        width: 150,
        height: 100,
      },
      sizeOne: {
        width: $r('app.float.Length_Resource_150'),
        height: $r('app.float.Length_Resource_100'),
      },

      position: undefined,
    },
    {
      toastInfo: '宽高设置负值',

      size: {
        width: -150,
        height: -100,

      },
      sizeOne: {
        width: $r('app.float.Length_Resource_minus_150'),
        height: $r('app.float.Length_Resource_minus_100'),
      },

      position: { x: 50, y: 50 },
    },
    {
      toastInfo: '宽高设置0',

      size: {
        width: 0,
        height: 0,
      },
      sizeOne: {
        width: $r('app.float.Length_Resource_0'),
        height: $r('app.float.Length_Resource_0'),
      },
      position: { x: -50, y: -50 },
    },
    {
      toastInfo: '宽高设置大的正常值',
      size: {
        width: 360,
        height: 100,
      },
      sizeOne: {
        width: $r('app.float.Length_Resource_360'),
        height: $r('app.float.Length_Resource_100'),
      },

    },
    {
      toastInfo: '宽高设置超大的正常值',

      size: {
        width: 500,
        height: 100,
      },
      sizeOne: {
        width: $r('app.float.Length_Resource_500'),
        height: $r('app.float.Length_Resource_100'),
      },

    },

    //宽高百分比
    {
      toastInfo: '宽高设置正常值',

      size: {
        width: '40%',
        height: '20%',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_40percent'),
        height: $r('app.string.Length_Resource_20percent'),
      },

    },
    {
      toastInfo: '宽高设置正常值',

      size: {
        width: '40',
        height: '20',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_40'),
        height: $r('app.string.Length_Resource_20'),
      },

    },
    {
      toastInfo: '宽高设置负值',

      size: {
        width: '-40%',
        height: '-20%',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_minus_40percent'),
        height: $r('app.string.Length_Resource_minus_20percent'),
      },

    },
    {
      toastInfo: '宽高设置负值',

      size: {
        width: '-40',
        height: '-20',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_minus_40'),
        height: $r('app.string.Length_Resource_minus_20'),
      },

    },
    {
      toastInfo: '宽高设置0',

      size: {
        width: '0%',
        height: '0%',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_0percent'),
        height: $r('app.string.Length_Resource_0percent'),
      },

    },
    {
      toastInfo: '宽高设置0',

      size: {
        width: '0',
        height: '0',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_0'),
        height: $r('app.string.Length_Resource_0'),
      },

    },
    {
      toastInfo: '宽高设置大的正常值',

      size: {
        width: '98%',
        height: '40%',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_98percent'),
        height: $r('app.string.Length_Resource_40percent'),
      },

    },
    {
      toastInfo: '宽高设置大的正常值',

      size: {
        width: '98',
        height: '40',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_98'),
        height: $r('app.string.Length_Resource_40'),
      },

    },
    {
      toastInfo: '宽高设置超大正常值',

      size: {
        width: '120%',
        height: '40%',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_120percent'),
        height: $r('app.string.Length_Resource_40percent'),
      },

    },
    {
      toastInfo: '宽高设置超大正常值',

      size: {
        width: '120',
        height: '40',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_120'),
        height: $r('app.string.Length_Resource_40'),
      },

    },

    {
      toastInfo: '宽高设置文本字符串',

      size: {
        width: '120percent',
        height: '40percent',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_120_percent'),
        height: $r('app.string.Length_Resource_40_percent'),
      },

    },
    {
      toastInfo: '宽高设置带单位px的数字字符串',

      size: {
        width: '120px',
        height: '40px',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_120px'),
        height: $r('app.string.Length_Resource_40px'),
      },

    },
    {
      toastInfo: '宽高设置带单位vp的数字字符串',

      size: {
        width: '120vp',
        height: '40vp',
      },
      sizeOne: {
        width: $r('app.string.Length_Resource_120vp'),
        height: $r('app.string.Length_Resource_40vp'),
      },

    },

  ]

  private setParam(): void {
    this.toastInfo = this.sets[this.index].toastInfo

    this.sizeOne = this.sets[this.index].size
    this.sizeTwo = this.sets[this.index].sizeOne

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
            this.lastIndex = this.index
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
            this.lastIndex = this.index
            this.calcIndex = this.index

          }
        })

      }
      .margin({ top: 10 })

      Column() {

        Counter() {

          Text(this.value.toString())
        }

        .size(this.sizeOne)
        .margin(10)

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


        .size(this.sizeTwo)
        .margin(10)

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