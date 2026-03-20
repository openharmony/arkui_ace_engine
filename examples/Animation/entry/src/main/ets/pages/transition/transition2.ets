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

// xxx.ets
@Entry
@Component
struct TransitionEffectExample2 {
  @State flag: boolean = true;
  @State show: string = 'show';

  build() {
    Column() {
      Button(this.show).width(80).height(30).margin(30)
        .onClick(() => {
          // 点击Button控制Image的显示和消失
          if (this.flag) {
            this.show = 'hide';
          } else {
            this.show = 'show';
          }
          animateTo({ duration: 2000 }, () => {
            // 第一张图的TransitionEffect包含了animation，transition的动画参数由TransitionEffect指定
            // 第二张图的TransitionEffect不包含animation，transition的动画参数由animateTo指定
            this.flag = !this.flag;
          });
        })
      if (this.flag) {
        // Image的显示和消失配置为不同的过渡效果
        // 出现时做从指定的透明度为0变为默认的透明度1的动画，该动画时长为1000ms，以及做从指定的绕z轴旋转180°变为默认的旋转角为0的动画，该动画1000ms后播放，时长为1000ms
        // 消失时做从默认的透明度为1变为指定的透明度0的动画，该动画1000ms后播放，时长为1000ms，以及做从默认的旋转角0变为指定的绕z轴旋转180°的动画，该动画时长为1000ms
        Image($r('app.media.aaa')).width(200).height(200)
          .transition(
            TransitionEffect.asymmetric(
              TransitionEffect.OPACITY.animation({ duration: 1000 }).combine(
                TransitionEffect.rotate({ z: 1, angle: 180 }).animation({ delay: 1000, duration: 1000 }))
              ,
              TransitionEffect.OPACITY.animation({ delay: 1000, duration: 1000 }).combine(
                TransitionEffect.rotate({ z: 1, angle: 180 }).animation({ duration: 1000 }))
            )
          )
        // 出现时做从x方向和y方向scale都为0变为默认的x方向和y方向scale都为1的动画，该动画时长为animateTo中指定的2000ms
        // 消失时无转场效果
        Image($r('app.media.aaa')).width(200).height(200).margin({ top: 100 })
          .transition(
            TransitionEffect.asymmetric(
              TransitionEffect.scale({ x: 0, y: 0 }),
              TransitionEffect.IDENTITY
            )
          )
      }
    }.width('100%')
  }
}