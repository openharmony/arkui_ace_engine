/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { Animator as animator, AnimatorResult, SimpleAnimatorOptions } from '@kit.ArkUI';

@Entry
@Component
struct SimpleOptionsAnimator {
  private TAG: string = '[AnimatorTest]'
  private backAnimator: AnimatorResult | undefined = undefined
  private flag: boolean = false
  private resetOptions: SimpleAnimatorOptions = new SimpleAnimatorOptions(100, 300)
    .duration(3000)
    .easing("ease-in")
    .delay(0)
    .fill(FillMode.Forwards)
    .direction(PlayMode.Alternate)
    .iterations(3)

  @State wid: number = 100
  @State hei: number = 100

  @State begin: number | undefined = 100
  @State end: number | undefined = 200
  @State dur: number | undefined = 1000
  @State ease: string | undefined = "ease"
  @State delay: number | undefined = 0
  @State fill: FillMode | undefined = FillMode.Forwards
  @State dir: PlayMode | undefined = PlayMode.Normal
  @State iter: number | undefined = 1

  create() {
    if (this.backAnimator) {
      this.backAnimator.finish()
    }
    this.backAnimator = animator.create(
      new SimpleAnimatorOptions(this.begin, this.end)
        .duration(this.dur)
        .easing(this.ease)
        .delay(this.delay)
        .fill(this.fill)
        .direction(this.dir)
        .iterations(this.iter)
    )
    this.backAnimator.onFinish = ()=> {
      this.flag = true
      console.info(this.TAG, 'backAnimator onfinish')
    }
    this.backAnimator.onRepeat = ()=> {
      console.info(this.TAG, 'backAnimator repeat')
    }
    this.backAnimator.onCancel = ()=> {
      console.info(this.TAG, 'backAnimator cancel')
    }
    this.backAnimator.onFrame = (value:number)=> {
      this.wid = value
      this.hei = value
    }
  }

  aboutToDisappear() {
    // 由于backAnimator在onframe中引用了this, this中保存了backAnimator，
    // 在自定义组件消失时应该将保存在组件中的backAnimator置空，避免内存泄漏
    this.backAnimator = undefined;
  }

  build() {
    Column() {
      Column() {
        Column()
          .width(this.wid)
          .height(this.hei)
          .backgroundColor(Color.Red)
      }
      .width('100%')
      .height(300)

      Column() {
        Column() {
          Row() {
            Text('begin: ')
            Text(`${this.begin}`)
            Button('-10')
              .onClick(() => {
                if (this.begin !== undefined) {
                  this.begin -= 10
                }
              })
            Button('+10')
              .onClick(() => {
                if (this.begin !== undefined) {
                  this.begin += 10
                }
              })
            Button('undefined')
              .onClick(() => {
                if (this.begin === undefined) {
                  this.begin = 100
                } else {
                  this.begin = undefined
                }
              })
          }

        }
        Column() {
          Row() {
            Text('end: ')
            Text(`${this.end}`)
            Button('-10')
              .onClick(() => {
                if (this.end !== undefined) {
                  this.end -= 10
                }
              })
            Button('+10')
              .onClick(() => {
                if (this.end !== undefined) {
                  this.end += 10
                }
              })
            Button('undefined')
              .onClick(() => {
                if (this.end === undefined) {
                  this.end = 200
                } else {
                  this.end = undefined
                }
              })
          }
        }
        Column() {
          Row() {
            Text('duration: ')
            Text(`${this.dur}`)
            Button('-100')
              .onClick(() => {
                if (this.dur !== undefined) {
                  this.dur -= 100
                }
              })
            Button('+100')
              .onClick(() => {
                if (this.dur !== undefined) {
                  this.dur += 100
                }
              })
            Button('undefined')
              .onClick(() => {
                if (this.dur === undefined) {
                  this.dur = 1000
                } else {
                  this.dur = undefined
                }
              })
          }

        }
        Column() {
          Row() {
            Text('easing: ')
            Text(`${this.ease}`)
            Select([{ value: 'ease' },
              { value: 'ease-in' },
              { value: 'ease-out' },
              { value: 'ease-in-out' },
              { value: 'fast-out-slow-in' },
              { value: 'linear-out-slow-in' },
              { value: 'fast-out-linear-in' },
              { value: 'friction' },
              { value: 'extreme-deceleration' },
              { value: 'rhythm' },
              { value: 'smooth' },
            ])
              .value(this.ease)
              .onSelect((index:number, text?: string | undefined)=>{
                if(text){
                  console.log("cwcvvv :", text);
                  this.ease = text;
                }
              })
            Button('undefined')
              .onClick(() => {
                if (this.ease === undefined) {
                  this.ease = "ease"
                } else {
                  this.ease = undefined
                }
              })
          }
        }
        Column() {
          Row() {
            Text('delay: ')
            Text(`${this.delay}`)
            Button('-1')
              .onClick(() => {
                if (this.delay !== undefined) {
                  this.delay -= 1
                }
              })
            Button('+1')
              .onClick(() => {
                if (this.delay !== undefined) {
                  this.delay += 1
                }
              })
            Button('undefined')
              .onClick(() => {
                if (this.delay === undefined) {
                  this.delay = 0
                } else {
                  this.delay = undefined
                }
              })
          }
        }
        Column() {
          Row() {
            Text('fill: ')
            Text(`${this.fill}`)
            Select([{ value: 'none' },
              { value: 'forward' },
              { value: 'backwards' },
              { value: 'both' },
            ])
              .onSelect((index:number, text?: string | undefined)=>{
                if(text){
                  console.log("cwcvvv fill :", text);
                  if (text == 'none') {
                    this.fill = FillMode.None
                  } else if (text == 'forward') {
                    this.fill = FillMode.Forwards
                  } else if (text == 'backwards') {
                    this.fill = FillMode.Backwards
                  } else {
                    this.fill = FillMode.Both
                  }
                }
              })
            Button('undefined')
              .onClick(() => {
                if (this.fill === undefined) {
                  this.fill = FillMode.Backwards
                } else {
                  this.fill = undefined
                }
              })
          }
        }
        Column() {
          Row() {
            Text('direction: ')
            Text(`${this.dir}`)
            Select([{ value: 'normal' },
              { value: 'alternate' },
              { value: 'reverse' },
              { value: 'alternate-reverse' },
            ])
              .onSelect((index: number, text?: string | undefined) => {
                if (text) {
                  console.log("cwcvvv direction :", text);
                  if (text == 'normal') {
                    this.dir = PlayMode.Normal
                  } else if (text == 'alternate') {
                    this.dir = PlayMode.Alternate
                  } else if (text == 'reverse') {
                    this.dir = PlayMode.Reverse
                  } else {
                    this.dir = PlayMode.AlternateReverse
                  }
                }
              })
            Button('undefined')
              .onClick(() => {
                if (this.dir === undefined) {
                  this.dir = PlayMode.Normal
                } else {
                  this.dir = undefined
                }
              })
          }
        }
        Column() {
          Row() {
            Text('iterations: ')
            Text(`${this.iter}`)
            Button('-1')
              .onClick(() => {
                if (this.iter !== undefined) {
                  this.iter -= 1
                }
              })
            Button('+1')
              .onClick(() => {
                if (this.iter !== undefined) {
                  this.iter += 1
                }
              })
            Button('undefined')
              .onClick(() => {
                if (this.iter === undefined) {
                  this.iter = 1
                } else {
                  this.iter = undefined
                }
              })
          }
        }
        Row() {
          Row() {
            Button('create')
              .fontSize(20)
              .fontColor(Color.Black)
              .onClick(() => {
                try {
                  this.create()
                } catch(error) {
                  console.info("cwcsss", error.message)
                }
              })
          }
          .padding(10)

          Row() {
            Button('play')
              .fontSize(20)
              .fontColor(Color.Black)
              .onClick(() => {
                this.flag = false
                if(this.backAnimator){
                  this.backAnimator.play()
                }
              })
          }
          .padding(10)

          Row() {
            Button('pause')
              .fontSize(20)
              .fontColor(Color.Black)
              .onClick(() => {
                if(this.backAnimator){
                  this.backAnimator.pause()
                }
              })
          }
          .padding(10)
        }

        Row() {
          Row() {
            Button('finish')
              .fontSize(20)
              .fontColor(Color.Black)
              .onClick(() => {
                this.flag = true
                if(this.backAnimator){
                  this.backAnimator.finish()
                }
              })
          }
          .padding(10)

          Row() {
            Button('reverse')
              .fontSize(20)
              .fontColor(Color.Black)
              .onClick(() => {
                this.flag = false
                if(this.backAnimator){
                  this.backAnimator.reverse()
                }
              })
          }
          .padding(10)

          Row() {
            Button('cancel')
              .fontSize(20)
              .fontColor(Color.Black)
              .onClick(() => {
                if(this.backAnimator){
                  this.backAnimator.cancel()
                }
              })
          }
          .padding(10)
        }


        Row() {
          Button('reset')
            .fontSize(20)
            .fontColor(Color.Black)
            .onClick(() => {
              if (this.flag) {
                this.flag = false
                if(this.backAnimator){
                  this.backAnimator.reset(this.resetOptions)
                }
              } else {
                console.info(this.TAG, 'Animation not ended')
              }
            })
        }
        .padding(10)
      }
    }
  }
}