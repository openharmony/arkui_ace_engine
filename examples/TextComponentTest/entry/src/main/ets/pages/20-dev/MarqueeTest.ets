/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import font from '@ohos.font';
@Entry
@Component
struct Marquee3018 {
  @State start: boolean = false
  @State src: string = '君不见，黄河之水天上来，奔流到海不复回；君不见，高堂明镜悲白发，朝如青丝暮成雪。'
  @State marqueeUpdateStrategy: (MarqueeUpdateStrategy | undefined)[] = [MarqueeUpdateStrategy.DEFAULT, MarqueeUpdateStrategy.PRESERVE_POSITION, undefined]
  @State marqueeIndex: number = 0
  @State heightTest: number = 80
  @State widthTest: number = 250
  @State paddingTest: number = 0
  @State loop: number = 5
  @State step: number = 15
  @State fromStart: boolean = true
  @State onStart: number = 0
  @State onBounce: number = 0
  @State onFinish: number = 0
  @State fontSize: number = 16
  @State allowScale: boolean[]= [false,true]
  @State allowScaleStr: string[]= ['false','true']
  @State allowScaleIndex: number= 0

  @State fontWeight: (FontWeight | number | undefined | string)[] = [100,200,300,400,500,600,700,800,900,0,1000,undefined,'205abc',FontWeight.Lighter,FontWeight.Normal,FontWeight.Regular,FontWeight.Medium,FontWeight.Bold,FontWeight.Bolder]
  @State fontWeightStr: string[] = ['100','200','300','400','500','600','700','800','900','0','1000', 'undefined','205abc', 'Lighter','Normal','Regular','Medium','Bold','Bolder']
  @State fontWeightIndex: number = 3

  @State fontColor: Color[] = [Color.Black, Color.Blue, Color.Green, Color.Red, Color.Yellow]
  @State fontColorStr: string[] = ["Color.Black", "Color.Blue", "Color.Green", "Color.Red, Color.Yellow"]
  @State fontColorIndex: number = 0

  aboutToAppear() {
    font.registerFont({
      familyName: 'Red',
      familySrc: $rawfile('color.json')
    })
  }

  build() {
      Column({ space: 10 }) {
        // Text('onStart触发次数: ' + this.onStart)
        Text('onBounce触发次数: ' + this.onBounce)
          .fontColor('Red')
        // Text('onFinish触发次数: ' + this.onFinish)
        Marquee({
          start: this.start,
          step: this.step,
          src: this.src,
          loop: this.loop,
          fromStart: this.fromStart
        })
          .borderWidth(1)
          .borderColor(Color.Blue)
          .allowScale(this.allowScale[this.allowScaleIndex])
          .marqueeUpdateStrategy(this.marqueeUpdateStrategy[this.marqueeIndex])
          .width(this.widthTest)
          .height(this.heightTest)
          .padding(this.paddingTest)
          .fontSize(this.fontSize)
          .fontColor(this.fontColor[this.fontColorIndex])
          .fontWeight(this.fontWeight[this.fontWeightIndex])
          .fontFamily('HarmonyOS Sans')
          .margin({ bottom: '40vp' })
          .onStart(() => {
            this.onStart += 1
          })
          .onBounce(() => {
            this.onBounce += 1
            console.info('Succeeded in completing the onBounce callback of marquee animation');
          })
          .onFinish(() => {
            this.onFinish += 1
          })

        TextArea({ text: this.src })
          .onChange((value: string) => {
            this.src = value
          })

        Scroll() {
          Column() {
            Row() {
              Button('marqueeUpdateStrategy: ' + this.marqueeUpdateStrategy[this.marqueeIndex])
                .width(300)
                .onClick(() => {
                  this.marqueeIndex = (this.marqueeIndex + 1) % this.marqueeUpdateStrategy.length
                })
            }

            Row() {
              Button('fontSize+,' + this.fontSize).onClick((event: ClickEvent) => {
                this.fontSize += 2
              }).margin(2)
                .width(150)
              Button('fontSize-,' + this.fontSize).onClick((event: ClickEvent) => {
                this.fontSize -= 2
              }).margin(2)
                .width(150)
            }

            Row() {
              Button('step+ :' + this.step).onClick((event: ClickEvent) => {
                this.step += 2
              }).margin(2)
                .width(150)
              Button('step- :' + this.step).onClick((event: ClickEvent) => {
                this.step -= 2
              }).margin(2)
                .width(150)
            }

            Row() {
              Button('fontWeight:' + this.fontWeightStr[this.fontWeightIndex])
                .width(150)
                .onClick(() => {
                  this.fontWeightIndex = (this.fontWeightIndex + 1) % this.fontWeight.length
                })

              Button('fontColor:' + this.fontColorStr[this.fontColorIndex])
                .width(150)
                .onClick(() => {
                  this.fontColorIndex = (this.fontColorIndex + 1) % this.fontColor.length
                })
            }.margin({ top: 5 })

            Row() {
              Button('start: ' + this.start)
                .width(150)
                .onClick(() => {
                  this.start = !this.start
                })
              Button('fromStart: ' + this.fromStart)
                .width(150)
                .onClick(() => {
                  this.fromStart = !this.fromStart
                })
            }

            Row() {
              Button('loop+,' + this.loop)
                .width(150)
                .onClick(() => {
                  this.loop += 1
                })

              Button('loop-,' + this.loop)
                .width(150)
                .onClick(() => {
                  this.loop -= 1
                })
            }

            Row() {
              Button('height+,' + this.heightTest)
                .width(150)
                .onClick(() => {
                  this.heightTest += 10
                })

              Button('height-,' + this.heightTest)
                .width(150)
                .onClick(() => {
                  this.heightTest -= 10
                })
            }

            Row() {
              Button('width+,' + this.widthTest)
                .width(150)
                .onClick(() => {
                  this.widthTest += 10
                })

              Button('width-,' + this.widthTest)
                .width(150)
                .onClick(() => {
                  this.widthTest -= 10
                })
            }

            Row() {
              Button('padding+,' + this.paddingTest)
                .width(150)
                .onClick(() => {
                  this.paddingTest += 10
                })

              Button('padding-,' + this.paddingTest)
                .width(150)
                .onClick(() => {
                  this.paddingTest -= 10
                })
            }

            Row() {
              Button('allowScale:' + this.allowScaleStr[this.allowScaleIndex])
                .width(150)
                .onClick(() => {
                  this.allowScaleIndex = (this.allowScaleIndex + 1) % this.allowScaleStr.length
                })

            }
          }
        }
      }
      .height('100%')
      .width('100%')
      // .height('60%')
  }
}