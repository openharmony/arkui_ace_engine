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
struct changeImage {
  @State message: Resource = $r('app.media.cat01');
  @State rotateAngle: number = 0
  @State name:string = '开始'

  build() {
    Column() {
      Image(this.message)
        .contentTransition(ContentTransitionEffect.OPACITY) // 图片切换时淡入淡出
        .alt($r('app.media.startIcon')) // 图片加载失败时显示的替代资源
        .width(300)
        .height(300)

      // 功能：点击切换为cloud图片，100ms后自动恢复为cat01
      Button(this.name, { type: ButtonType.Normal, stateEffect: false })
        .width(100)
        .height(100)
        .onClick(() => {
          console.info('change img_1')
          this.message = $r('app.media.cloud')
          setTimeout(()=>{
            this.message = $r('app.media.cat01')
          },100)
        });
    }
  }
}