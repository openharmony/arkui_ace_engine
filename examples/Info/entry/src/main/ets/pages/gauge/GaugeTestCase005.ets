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

class MyModifier0 implements AttributeModifier<GaugeAttribute> {

  public gaugeStyle:Array<obj> = [
  // 1
    {
      value:50,
      trackShadow: {radius:undefined,offsetX:undefined,offsetY:undefined},
      startAngle:0,
      endAngle:300,
      strokeWidth:-5,
      colors: Color.Red,
      indicator:{icon:$r('app.media.icon_play'),
        space:('100px')},
    },
    // 2
    {
      trackShadow:{radius:-5,offsetX:-20,offsetY:-20},
      value:-5,
      startAngle:60,
      endAngle:40,
      strokeWidth:'50%',
      colors: 'rgb(255, 100, 255)',
      indicator:{icon:$r('app.media.icon_play'),
        space:('100vp')},
    },
    // 3
    {
      trackShadow:{radius:10,offsetX:20,offsetY:20},
      startAngle:-100,
      endAngle:-160,
      strokeWidth:50,
      colors:'#ff0000ff',
      indicator:{icon:$r('app.media.icon_play'),
        space:('100fp')},
    },
    // 4
    {
      trackShadow:{radius:40,offsetX:80,offsetY:80},
      value: 30,
      startAngle:370,
      endAngle:360,
      strokeWidth:0,
      colors:
      (
        [
          [new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
          [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
          [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
          [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
          [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
          [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
          [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
          [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
          [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]), 1]
        ]
      ),
      indicator:{icon:$r('app.media.icon_play'),
        space:('100lpx')},
    },
    // 5
    {
      trackShadow: {radius:$r('app.string.rRadius'),
        offsetX:$r('app.string.rOffset'),
        offsetY:$r('app.string.rOffset')
      },
      value:500,
      startAngle:60,
      endAngle:-90,
      strokeWidth:undefined,
      colors:0xBBFFFF,
      indicator:{icon:$r('app.media.icon_play'),
        space:('50%')},
    },
    // 6
    {
      startAngle:90,
      endAngle:120,
      value:50,
      indicator:{icon:$r('app.media.icon_play'),
        space:($r('app.string.number_70'))},
      colors:$r('app.color.rColor1'),
      strokeWidth:$r('app.string.number_15'),
    },
    // 7
    {
      startAngle:90,
      endAngle:120,
      value:50,
      indicator:{icon:$r('app.media.pen'),space:(12)},
      colors:'rgba(255, 100, 255, 0.5)',
      strokeWidth:'fdsfsdcxvgdfs'
    },
    // 8
    {
      indicator:{icon:$r('app.media.pen'),space:(2000)},
      colors:
      new LinearGradient([{ color: '#ff0000ff', offset: 0.4 },
        { color: 'rgb(255, 100, 255)', offset: 0.2 },
        { color: 0xBBFFFF, offset: 2 }]),
      strokeWidth:'100px'
    },
    // 9
    {
      indicator:{icon:$r('app.media.pen'),space:(-5)},
      colors:
      new LinearGradient([{ color: Color.Orange, offset: -0.3 },
        { color: 'rgba(255, 100, 255, 0.5)', offset: 0.5 },
        { color: $r('app.color.rColor1'), offset: 2 }]),
      strokeWidth:1000
    },
  ]
  public num: number = 0

  applyNormalAttribute(instance: GaugeAttribute): void {
    instance.indicator(this.gaugeStyle[this.num].indicator)
    instance.trackShadow(this.gaugeStyle[this.num].trackShadow)
    instance.colors(this.gaugeStyle[this.num].colors)
    instance.value(this.gaugeStyle[this.num].value)
    instance.startAngle(this.gaugeStyle[this.num].startAngle)
    instance.endAngle(this.gaugeStyle[this.num].endAngle)
    instance.strokeWidth(this.gaugeStyle[this.num].strokeWidth)

  }
}

interface GaugeShadowOptions1{
  radius?:number | Resource
  offsetX?:number | Resource
  offsetY?:number | Resource
}


interface obj {
  indicator?:GaugeIndicatorOptions
  trackShadow?:GaugeShadowOptions1
  colors?:	ResourceColor | LinearGradient | Array<[ResourceColor | LinearGradient, number]>
  value?:number
  startAngle?:number
  endAngle?:number
  strokeWidth?:Length
  description?:CustomBuilder
}

@Entry
@Component
struct GaugeLevel1_0 {
  @State mod1: MyModifier0 = new MyModifier0()
  build() {
    Column(){
      Text('GaugeStyle属性测试').fontSize(9).fontColor(0xCCCCCC).width('100%')
      Column() {
        Gauge({value:this.mod1.gaugeStyle[this.mod1.num].value} )
          .attributeModifier(this.mod1)
        Divider().height(10)
        Gauge({value:this.mod1.gaugeStyle[this.mod1.num].value} )
          .indicator(this.mod1.gaugeStyle[this.mod1.num].indicator)
          .trackShadow(this.mod1.gaugeStyle[this.mod1.num].trackShadow)
          .colors(this.mod1.gaugeStyle[this.mod1.num].colors)
          .value(this.mod1.gaugeStyle[this.mod1.num].value)
          .startAngle(this.mod1.gaugeStyle[this.mod1.num].startAngle)
          .endAngle(this.mod1.gaugeStyle[this.mod1.num].endAngle)
          .strokeWidth(this.mod1.gaugeStyle[this.mod1.num].strokeWidth)

      }

      Row({ space: 2 }) {
        Text(`${this.mod1.num + 1}/`)
        Text(`${this.mod1.gaugeStyle.length}`)
        Button() {
          Text('Index++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
        }
        .onClick(() => {
          this.mod1.num++
          if (this.mod1.num > this.mod1.gaugeStyle.length - 1) {
            this.mod1.num = 0
          }
        })

        Button() {
          Text('Index--')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
        }
        .onClick(() => {
          this.mod1.num--
          if (this.mod1.num < 0) {
            this.mod1.num = this.mod1.gaugeStyle.length - 1
          }
        })
      }
    }.height('100%')
  }
}
