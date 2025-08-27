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

/*
 * This code defines a component named 'ImageAnimatorExample' that demonstrates and tests various layout behaviors 
 * and clipping features of the 'ImageAnimator' component.
 * 
 * It includes:
 * - State variables for managing UI interactions such as background color, visibility of image animators, and clip 
 * toggling.
 * - Multiple 'ImageAnimator' components with different configurations to test:
 *   - Layout behavior with and without explicitly set width and height.
 *   - Use of 'clip' to control visual clipping of the animated image content.
 *   - Interaction with common attributes like 'borderWidth', 'borderRadius', 'padding', and 'backgroundColor'.
 *   - Dynamic updates through user interaction (e.g., click and touch events).
 * - Functional testing of 'size', 'aspectRatio', 'layoutWeight', and nested image configurations.
 * - Lifecycle callbacks such as 'onAppear' and 'onDisAppear' to track visibility changes.
 */

@Entry
@Component
struct ImageAnimatorExample {
  @State text: string = ''
  @State bgColor: Color = Color.Orange
  @State showImageAnimator: boolean = true
  @State clip1: boolean = false

  build() {
    Column() {
      Text('ImageAnimator组件 布局及剪裁测试').fontSize(12).fontColor(0xCCCCCC).width('100%').margin(10)
      Text('ImageAnimator组件设置宽高 通用clip: ' + this.clip1)
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .key('clip')
        .onClick(() => {
          this.clip1 = !this.clip1
        })
      ImageAnimator()
        .images([
          {
            src: '/common/png_478_659.PNG'
          },
          {
            src: '/common/jpg_240_160.jpg'
          }
        ])
        .width(200)
        .aspectRatio(2)
        .borderWidth(1)
        .borderRadius(100)
        .clip(this.clip1)
      Text('ImageAnimator组件设置宽高 验证剪裁效果').fontSize(9).fontColor(0xCCCCCC).width('100%')
      ImageAnimator()
        .images([
          {
            src: $r('app.media.jpeg_690_669')
          },
          {
            src: $r('app.media.ic_bmp')
          },
        ])
        .size({ width: '100%', height: '20%' })
        .margin(10)
        .borderWidth(1)
        .borderRadius(100)
      //imageAnimator不设宽高
      Text('ImageAnimator组件不设置宽高 验证布局逻辑').fontSize(9).fontColor(0xCCCCCC).width('100%').margin(10)
      Text(this.text).fontColor(Color.Gray)
      if (this.showImageAnimator) {
        //images里面设置宽高，取images里面宽高最大值作为自身宽高
        ImageAnimator()
          .images([
            {
              src: $r('app.media.jpeg_690_669'),
              width: 30,
              height: 30
            },
            {
              src: '/common/png_478_659.PNG',
              width: 50,
              height: 50,
            },
          ])
          .fixedSize(false)
          .borderWidth(1)
          .key('imageAnimator1')
          .onClick(() => {
            this.showImageAnimator = !this.showImageAnimator
          })
          .onAppear(() => {
            this.text = 'hbx imageAnimator onAppear'
          })
          .onDisAppear(() => {
            this.text = 'hbx imageAnimator onDisAppear'
          })
      } else {
        //images厘米不设置宽高，不显示？
        ImageAnimator()
          .images([
            {
              src: $r('app.media.jpeg_690_669'),
            },
            {
              src: '/common/png_478_659.PNG',
            },
          ])
          .fixedSize(false)
          .borderWidth(1)
          .key('imageAnimator2')
          .onClick(() => {
            this.showImageAnimator = !this.showImageAnimator
          })
      }
      Text('ImageAnimator组件设置宽高 验证与通用属性结合').fontSize(9).fontColor(0xCCCCCC).width('100%').margin(10)
      ImageAnimator()
        .images([
          {
            src: '/common/png_478_659.PNG',
            width: 200,
            height: '100vp'
          },
          {
            src: $r('app.media.jpeg_690_669'),
            width: '300vp',
            height: 50
          },
        ])
        .size({ height: '20%' })
        .borderWidth(1)
        .padding(20)
        .backgroundColor(this.bgColor)
        .layoutWeight(1)
        .key('imageAnimator3')
        .onTouch(() => {
          this.bgColor = Color.Green
        })
    }
  }

  pageTransition() {
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
    PageTransitionExit({ type: RouteType.None, duration: 0 })
  }
}