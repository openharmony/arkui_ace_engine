/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct AnimateToTest {
  // 声明一个状态变量，用于存储当前显示的图片资源，初始值为cat01图片
  // 注：$r('app.media.cloud1')等资源需替换为开发者实际使用的图像资源
  @State imageResource: Resource = $r('app.media.cat01')

  build() {
    Row() {
      Column() {
        Image(this.imageResource)
          .width(595)
          .height(842) 
          .objectFit(ImageFit.Contain) // 设置图片适配方式为保持比例缩放以完全显示
          .borderWidth(10) // 设置图片边框宽度
          .contentTransition(ContentTransitionEffect.OPACITY) // 启用淡入淡出的内容过渡效果
          .onClick(() => { 
            // 调用animateTo方法实现动画过渡，空对象表示使用默认动画配置
            animateTo({}, () => {
              // 在动画回调中修改图片资源，触发图片切换并应用过渡效果
              this.imageResource = $r('app.media.cloud')
            })
          })
        Button()
      }
      .width('100%') 
    }
    .height('100%') 
  }
}