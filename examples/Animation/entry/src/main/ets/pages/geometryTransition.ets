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

import router from '@ohos.router';
@Entry
@Component
struct GeometryTransition {
  @State isShow: boolean = false

  build() {
    Column() {
      Column() {
        Button("返回")
          .onClick(() => {
            router.back()
          })
      }
      .width('100%')
      .height('10%')
      .backgroundColor(Color.Orange)
      .justifyContent(FlexAlign.Center)
      Stack({ alignContent: Alignment.Center }) {
        if (this.isShow) {
          Image($r('app.media.ccc'))
            .autoResize(false)
            .clip(true)
            .width(300)
            .height(400)
            .offset({ y: 100 })
            .geometryTransition("picture", { follow: false })
            .transition(TransitionEffect.OPACITY)
        } else {
          // geometryTransition此处绑定的是容器，那么容器内的子组件需设为相对布局跟随父容器变化，
          // 套多层容器为了说明相对布局约束传递
          Column() {
            Column() {
              Image($r('app.media.startIcon'))
                .width('100%').height('100%')
            }.width('100%').height('100%')
          }
          .width(80)
          .height(80)
          // geometryTransition会同步圆角，但仅限于geometryTransition绑定处，此处绑定的是容器
          // 则对容器本身有圆角同步而不会操作容器内部子组件的borderRadius
          .borderRadius(20)
          .clip(true)
          .geometryTransition("picture")
          // transition保证组件离场不被立即析构，可设置其他转场效果
          .transition(TransitionEffect.OPACITY)
        }
      }
      .onClick(() => {
        animateTo({ duration: 1000 }, () => {
          this.isShow = !this.isShow
        })
      })
    }
  }
}