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
struct TransitionEffectExample3 {
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
          this.flag = !this.flag;
        })
      if (this.flag) {
        // 改flag条件时，会触发id为"column1"、"image1"、"image2"的transition动画。
        // id为"column1"的组件是这棵新出现/消失的子树的根节点。
        Column() {
          Row() {
            Image($r('app.media.bbb')).width(150).height(150).id("image1")
              .transition(TransitionEffect.OPACITY.animation({ duration: 1000 }))
          }
          Image($r('app.media.bbb')).width(150).height(150).margin({top: 50}).id("image2")
            .transition(TransitionEffect.scale({x: 0, y: 0}).animation({ duration: 1000 }))
          Text("view").margin({top: 50})
        }
        .id("column1")
        .transition(TransitionEffect.opacity(0.99).animation({ duration: 1000 }),
          // 结束回调设置在消失的第一层节点上，确保能有消失的结束回调
          (transitionIn: boolean) => {
            console.info("transition finish, transitionIn:" + transitionIn);
          }
        )
      }
    }.width('100%')
  }
}