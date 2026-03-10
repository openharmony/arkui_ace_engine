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

class MyModifier implements AttributeModifier<TabsAttribute> {
  text: string = '';
  currentIndex: number = 0;
  selectedIndex: number = 0;
  isOnContentDidScrollIndex: number = 0
  isVertical: boolean[] = [true, false]
  isVerticalIndex: number = 0
  isScrollable: boolean[] = [true, false]
  isScrollableIndex: number = 0
  isAnimationMode: AnimationMode[] =
    [
      AnimationMode.CONTENT_FIRST,
      AnimationMode.ACTION_FIRST,
      AnimationMode.NO_ANIMATION,
      AnimationMode.CONTENT_FIRST_WITH_JUMP,
      AnimationMode.ACTION_FIRST_WITH_JUMP
    ]
  isAnimationModeIndex: number = 0
  isPageFlipMode: PageFlipMode[] = [PageFlipMode.CONTINUOUS, PageFlipMode.SINGLE]
  isPageFlipModeIndex: number = 0
  clickedContent: string = '';
  onAnimationStart: string = ''
  onAnimationEnd: string = ''
  onGestureSwipe: string = ''
  onUnselected: number = 0
  // selectedIndex: number = 2
  // currentIndex: number = 2
  selfFadingFade: boolean = true;
  animationDuration: number[] = [600, 0]
  animationDurationIndex: number = 0
  isOnContentDidScroll: Array<OnTabsContentDidScrollCallback | undefined> = [
    ((selectedIndex: number, index: number, position: number, mainAxisLength: number) => {
      // 监听Swiper页面滑动事件，在该回调中可以实现自定义导航点切换动画等
      console.info("ygl onContentDidScroll selectedIndex: " + selectedIndex + ", index: " + index +
        ", position: " + position + ", mainAxisLength: " + mainAxisLength);
      this.text = "onContentDidScroll: \n"
        + "selectedIndex: " + selectedIndex + ';\n'
        + "index: " + index + ';\n'
        + "position: " + position + ';\n'
        + "mainAxisLength: " + mainAxisLength
    }),
    undefined]

  applyNormalAttribute(instance: TabsAttribute): void {
    instance.onContentDidScroll(this.isOnContentDidScroll[this.isOnContentDidScrollIndex])
    instance.vertical(this.isVertical[this.isVerticalIndex])
    instance.scrollable(this.isScrollable[this.isScrollableIndex])
    instance.animationMode(this.isAnimationMode[this.isAnimationModeIndex])
    instance.pageFlipMode(this.isPageFlipMode[this.isPageFlipModeIndex])
    instance.barMode(BarMode.Scrollable)
    instance.animationDuration(this.animationDuration[this.animationDurationIndex])
    instance.barOverlap(true)
    instance.barBackgroundBlurStyle(BlurStyle.COMPONENT_THICK)
    instance.onTabBarClick((index: number) => {
      this.clickedContent += 'now index ' + index + ' is clicked\n';
    })
    instance.onAnimationStart((index: number, targetIndex: number, extraInfo: TabsAnimationEvent) => {
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
    instance.onAnimationEnd((index: number, extraInfo: TabsAnimationEvent) => {
      console.info("ygl onAnimationEnd "
        + "index: " + index
        + "currentOffset: " + extraInfo.currentOffset
        + 'targetOffset: ' + extraInfo.targetOffset
        + 'velocity: ' + extraInfo.velocity);
    })
    instance.onGestureSwipe((index: number, extraInfo: TabsAnimationEvent) => {
      // 在页面跟手滑动过程中，逐帧触发该回调。
      console.info("ygl onGestureSwipe: "
        + "index: " + index
        + 'currentOffset: ' + extraInfo.currentOffset
        + 'targetOffset: ' + extraInfo.targetOffset
        + 'velocity: ' + extraInfo.velocity);
    })
    instance.onContentWillChange((currentIndex, comingIndex) => {
      if (comingIndex == 2) {
        return false;
      }
      return true;
    })
    instance.onSelected((index: number) => {
      console.log('ygl onSelected index:' + index);
      this.selectedIndex = index;
    })
    instance.onUnselected((index: number) => {
      console.log('ygl onUnselected index:' + index);
      this.onUnselected = index;
    })
    instance.fadingEdge(this.selfFadingFade)

  }
}

@Entry
@Component
struct Tabs_modifier {
  private controller: TabsController = new TabsController();

  private changeOrientation(isLandscape: boolean) {
    let context = getContext(this) as common.UIAbilityContext;
    window.getLastWindow(context).then((lastWindow) => {
      lastWindow.setPreferredOrientation(isLandscape ? window.Orientation.LANDSCAPE : window.Orientation.PORTRAIT)
    });
  }

  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State modifier: MyModifier = new MyModifier();
  @State currentIndex: number = 0;
  @State selectedIndex: number = 0

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
          Button('Vertical:' + this.modifier.isVertical[this.modifier.isVerticalIndex])
            .width('45%')
            .margin({ bottom: '12vp' })
            .onClick((event?: ClickEvent) => {
              this.modifier.isVerticalIndex++
              if (this.modifier.isVerticalIndex > this.modifier.isVertical.length - 1) {
                this.modifier.isVerticalIndex = 0
              }
            })
          Button('Scrollable:' + this.modifier.isScrollable[this.modifier.isScrollableIndex])
            .width('45%')
            .margin({ bottom: '12vp' })
            .onClick((event?: ClickEvent) => {
              this.modifier.isScrollableIndex++
              if (this.modifier.isScrollableIndex > this.modifier.isScrollable.length - 1) {
                this.modifier.isScrollableIndex = 0
              }
            })
        }

        Row() {
          Button('AnimationMode:' + this.modifier.isAnimationMode[this.modifier.isAnimationModeIndex])
            .width('45%')
            .margin({ bottom: '12vp' })
            .onClick((event?: ClickEvent) => {
              this.modifier.isAnimationModeIndex++
              if (this.modifier.isAnimationModeIndex > this.modifier.isAnimationMode.length - 1) {
                this.modifier.isAnimationModeIndex = 0
              }
            })
          Button('PageFlipMode:' + this.modifier.isPageFlipMode[this.modifier.isPageFlipModeIndex])
            .width('45%')
            .margin({ bottom: '12vp' })
            .onClick((event?: ClickEvent) => {
              this.modifier.isPageFlipModeIndex++
              if (this.modifier.isPageFlipModeIndex > this.modifier.isPageFlipMode.length - 1) {
                this.modifier.isPageFlipModeIndex = 0
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

        Button('onContentDidScroll:' + this.modifier.isOnContentDidScroll[this.modifier.isOnContentDidScrollIndex])
          .margin({ bottom: '12vp' })
          .onClick((event?: ClickEvent) => {
            this.modifier.isOnContentDidScrollIndex++
            if (this.modifier.isOnContentDidScrollIndex > this.modifier.isOnContentDidScroll.length - 1) {
              this.modifier.isOnContentDidScrollIndex = 0
            }
          })
        Button('animationDuration:' + this.modifier.animationDuration[this.modifier.animationDurationIndex])
          .width('45%')
          .margin({ bottom: '12vp' })
          .onClick((event?: ClickEvent) => {
            this.modifier.animationDurationIndex++
            if (this.modifier.animationDurationIndex > this.modifier.animationDuration.length - 1) {
              this.modifier.animationDurationIndex = 0
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
        .attributeModifier(this.modifier) //onContentDidScroll modifier
        .onChange((index: number) => {
          console.info(index.toString());
          this.currentIndex = index;
          this.selectedIndex = index;
        })
        .height(360)
        .width(360)
      }
      .padding({ top: '24vp', left: '24vp', right: '24vp' })
    }
  }
}