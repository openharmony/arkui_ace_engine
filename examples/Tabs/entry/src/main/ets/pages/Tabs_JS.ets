/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
import common from '@ohos.app.ability.common';
import window from '@ohos.window';
import { text } from '@kit.ArkGraphics2D';
import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';

@Entry
@Component
struct TabsOpaque {
  private controller: TabsController = new TabsController();

  private changeOrientation(isLandscape: boolean) {
    let context = getContext(this) as common.UIAbilityContext;
    window.getLastWindow(context).then((lastWindow) => {
      lastWindow.setPreferredOrientation(isLandscape ? window.Orientation.LANDSCAPE : window.Orientation.PORTRAIT)
    });
  }

  @State isOnContentDidScroll: Array<OnTabsContentDidScrollCallback | undefined> = [
    ((selectedIndex: number, index: number, position: number, mainAxisLength: number) => {
      // 监听Swiper页面滑动事件，在该回调中可以实现自定义导航点切换动画等
      console.info("ygl onContentDidScroll selectedIndex: " + selectedIndex + ", index: " + index +
        ", position: " + position + ", mainAxisLength: " + mainAxisLength);
    }),
    undefined]
  @State isOnContentDidScrollIndex: number = 0
  @State selfFadingFade: boolean = true;
  @State isVertical: boolean[] = [true, false]
  @State isVerticalIndex: number = 0
  @State isScrollable: boolean[] = [true, false]
  @State isScrollableIndex: number = 0
  @State text: string = ''
  @State isAnimationMode: AnimationMode[] =
    [
      AnimationMode.CONTENT_FIRST,
      AnimationMode.ACTION_FIRST,
      AnimationMode.NO_ANIMATION,
      AnimationMode.CONTENT_FIRST_WITH_JUMP,
      AnimationMode.ACTION_FIRST_WITH_JUMP
    ]
  @State isAnimationModeIndex: number = 0
  @State isPageFlipMode: PageFlipMode[] = [PageFlipMode.CONTINUOUS, PageFlipMode.SINGLE]
  @State isPageFlipModeIndex: number = 0
  @State clickedContent: string = ''
  @State onAnimationStart: string = ''
  @State onAnimationEnd: string = ''
  @State onGestureSwipe: string = ''
  @State onUnselected: number = 0
  @State selectedIndex: number = 0
  @State currentIndex: number = 0;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State animationDuration: number[] = [600, 0]
  @State animationDurationIndex: number = 0

  build() {
    Scroll() {
      Column() {
        Row() {
          Button("切换模式：浅色").width('45%').margin({ bottom: '12vp' })
            .onClick(() => {
              this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
            })
          Button("切换模式: 深色").width('45%').margin({ bottom: '12vp' })
            .onClick(() => {
              this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
            })
        }

        Row() {
          Button("竖屏").width('45%').margin({ bottom: '12vp' })
            .onClick(() => {
              this.changeOrientation(false)
            })
          Button("横屏").width('45%').margin({ bottom: '12vp' })
            .onClick(() => {
              this.changeOrientation(true)
            })
        }

        Row() {
          Button('Vertical:' + this.isVertical[this.isVerticalIndex]).width('45%').margin({ bottom: '12vp' })
            .onClick((event?: ClickEvent) => {
              this.isVerticalIndex++
              if (this.isVerticalIndex > this.isVertical.length - 1) {
                this.isVerticalIndex = 0
              }
            })
          Button('Scrollable:' + this.isScrollable[this.isScrollableIndex]).width('45%').margin({ bottom: '12vp' })
            .onClick((event?: ClickEvent) => {
              this.isScrollableIndex++
              if (this.isScrollableIndex > this.isScrollable.length - 1) {
                this.isScrollableIndex = 0
              }
            })
        }

        Row() {
          Button('AnimationMode:' + this.isAnimationMode[this.isAnimationModeIndex])
            .width('45%')
            .margin({ bottom: '12vp' })
            .onClick((event?: ClickEvent) => {
              this.isAnimationModeIndex++
              if (this.isAnimationModeIndex > this.isAnimationMode.length - 1) {
                this.isAnimationModeIndex = 0
              }
            })
          Button('PageFlipMode:' + this.isPageFlipMode[this.isPageFlipModeIndex])
            .width('45%')
            .margin({ bottom: '12vp' })
            .onClick((event?: ClickEvent) => {
              this.isPageFlipModeIndex++
              if (this.isPageFlipModeIndex > this.isPageFlipMode.length - 1) {
                this.isPageFlipModeIndex = 0
              }
            })
        }

        Row() {
          Button('index++:' + this.currentIndex).width('45%').margin({ bottom: '12vp' })
            .onClick(() => {
              this.currentIndex = (this.currentIndex + 1) % 8;
            })

          Button('changeIndex').width('45%').margin({ bottom: '12vp' })
            .onClick(() => {
              this.currentIndex = (this.currentIndex + 1) % 8;
              this.controller.changeIndex(this.currentIndex);
            })
        }

        Button('onContentDidScroll:' + this.isOnContentDidScroll[this.isOnContentDidScrollIndex])
          .margin({ bottom: '12vp' })
          .onClick((event?: ClickEvent) => {
            this.isOnContentDidScrollIndex++
            if (this.isOnContentDidScrollIndex > this.isOnContentDidScroll.length - 1) {
              this.isOnContentDidScrollIndex = 0
            }
          })
        Button('animationDuration:' + this.animationDuration[this.animationDurationIndex])
          .width('45%')
          .margin({ bottom: '12vp' })
          .onClick((event?: ClickEvent) => {
            this.animationDurationIndex++
            if (this.animationDurationIndex > this.animationDuration.length - 1) {
              this.animationDurationIndex = 0
            }
          })
        Text('onContentWillChange = 2')


        Tabs({ barPosition: BarPosition.Start, index: this.currentIndex, controller: this.controller }) {
          TabContent() {
            Column().width('100%').height('100%').backgroundColor(Color.Pink)
          }.tabBar('0_pink')

          TabContent() {
            Column().width('100%').height('100%').backgroundColor(Color.Yellow)
          }.tabBar('1_yellow')

          TabContent() {
            Column().width('100%').height('100%').backgroundColor(Color.Blue)
          }.tabBar('2_blue')

          TabContent() {
            Column().width('100%').height('100%').backgroundColor(Color.Red)
          }.tabBar('3_Red')

          TabContent() {
            Column().width('100%').height('100%').backgroundColor(Color.Gray)
          }.tabBar('4_Gray')

          TabContent() {
            Column().width('100%').height('100%').backgroundColor(Color.Brown)
          }.tabBar('5_Brown')

          TabContent() {
            Column().width('100%').height('100%').backgroundColor(Color.Orange)
          }.tabBar('6_Orange')

          TabContent() {
            Column().width('100%').height('100%').backgroundColor(Color.Black)
          }.tabBar('7_Black')
        }
        .onContentDidScroll(this.isOnContentDidScroll[this.isOnContentDidScrollIndex])
        .vertical(this.isVertical[this.isVerticalIndex])
        .scrollable(this.isScrollable[this.isScrollableIndex])
        .barMode(BarMode.Scrollable)
        .animationDuration(this.animationDuration[this.animationDurationIndex])
        .barOverlap(true)
        .barBackgroundBlurStyle(BlurStyle.COMPONENT_THICK)
        .animationMode(this.isAnimationMode[this.isAnimationModeIndex])
        .pageFlipMode(this.isPageFlipMode[this.isPageFlipModeIndex])
        .onChange((index: number) => {
          console.info(index.toString());
          this.currentIndex = index;
          this.selectedIndex = index;
        })
        .onAnimationStart((index: number, targetIndex: number, extraInfo: TabsAnimationEvent) => {
          if (index === targetIndex) {
            console.info("ygl onAnimationStart "
              + "index: " + index
              + "targetIndex: " + targetIndex
              + "currentOffset: " + extraInfo.currentOffset
              + 'targetOffset: ' + extraInfo.targetOffset
              + 'velocity: ' + extraInfo.velocity);
            return;
          }
        })
        .onAnimationEnd((index: number, extraInfo: TabsAnimationEvent) => {
          console.info("ygl onAnimationEnd "
            + "index: " + index
            + "currentOffset: " + extraInfo.currentOffset
            + 'targetOffset: ' + extraInfo.targetOffset
            + 'velocity: ' + extraInfo.velocity);
        }
        )
        .onGestureSwipe((index: number, extraInfo: TabsAnimationEvent) => {
          // 在页面跟手滑动过程中，逐帧触发该回调。
          console.info("ygl onGestureSwipe: "
            + "index: " + index
            + 'currentOffset: ' + extraInfo.currentOffset
            + 'targetOffset: ' + extraInfo.targetOffset
            + 'velocity: ' + extraInfo.velocity);

        })
        .onContentWillChange((currentIndex, comingIndex) => {
          if (comingIndex == 2) {
            console.info('ygl onContentWillChange = 2');
            return false;
          }
          return true;
        })
        .onSelected((index: number) => {
          console.log('ygl onSelected index:' + index);
          this.selectedIndex = index;
        })
        .onUnselected((index: number) => {
          console.log('ygl onUnselected index:' + index);
          this.onUnselected = index;
        })
        .fadingEdge(this.selfFadingFade)
        .height(360)
        .width(360)

      }
      .padding({ top: '24vp', left: '24vp', right: '24vp' })
    }
  }
}