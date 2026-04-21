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

/**
 * Image Resizable Zero Size Bug Demo
 * 
 * This demo reproduces a bug where Image component with resizable interface
 * may have dstRect size of 0 after component rebuild, causing the image not to display.
 * 
 * Root Cause:
 * When Image component is rebuilt (via if condition), loadingCtx_ is re-initialized,
 * and dstSize_ is reset to empty. If LoadingContext() is called before MakeCanvasImageIfNeed
 * correctly sets dstSize_, ResizableCalcDstSize() will calculate with empty dstSize_,
 * resulting in dstRect_ being 0.
 * 
 * Reproduction Steps:
 * 1. Set resizable interface on Image component
 * 2. Use if condition to rebuild the Image component
 * 3. Add transition animation to increase timing complexity
 * 4. Rapidly rebuild to increase probability of race condition
 */

@Entry
@Component
struct ImageResizableZeroSizeExample {
  @State flag: boolean = true;
  @State clickCount: number = 0;
  @State lastStatus: string = 'Ready';

  build() {
    Column({ space: 30 }) {
      Text('Image Resizable Zero Size Bug Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Text(`Rebuild Count: ${this.clickCount}`)
        .fontSize(16)

      Text(`Status: ${this.lastStatus}`)
        .fontSize(14)
        .fontColor('#666666')

      Stack() {
        if (this.flag) {
          Image($r('app.media.icon'))
            .width(200)
            .height(200)
            .objectFit(ImageFit.Contain)
            .resizable({
              slice: { top: 20, bottom: 20, left: 20, right: 20 }
            })
            .backgroundColor('#FFF0F0F0')
            .transition(
              TransitionEffect.OPACITY
                .animation({ duration: 300, curve: Curve.EaseInOut })
            )
            .onComplete(() => {
              this.lastStatus = 'Image loaded successfully';
              console.info('[ImageResizable] Image loaded successfully');
            })
            .onError((err: ImageLoadFailInfo) => {
              this.lastStatus = `Load failed: ${err.errorMessage || 'unknown'}`;
              console.error(`[ImageResizable] Image load failed: ${err.errorMessage}`);
            })
        }
      }
      .width(200)
      .height(200)
      .backgroundColor('#F5F5F5')
      .borderRadius(8)
      .border({ width: 1, color: '#CCCCCC' })

      Row({ space: 20 }) {
        Button('Rebuild Once')
          .onClick(() => {
            this.clickCount++;
            this.lastStatus = 'Rebuilding...';
            this.flag = false;
            setTimeout(() => {
              this.flag = true;
            }, 50);
          })

        Button('Rapid Rebuild 10x')
          .onClick(() => {
            this.lastStatus = 'Rapid rebuilding...';
            for (let i = 0; i < 10; i++) {
              setTimeout(() => {
                this.clickCount++;
                this.flag = false;
                setTimeout(() => {
                  this.flag = true;
                }, 20);
              }, i * 60);
            }
          })

        Button('Rapid Rebuild 20x')
          .onClick(() => {
            this.lastStatus = 'Rapid rebuilding...';
            for (let i = 0; i < 20; i++) {
              setTimeout(() => {
                this.clickCount++;
                this.flag = false;
                setTimeout(() => {
                  this.flag = true;
                }, 20);
              }, i * 50);
            }
          })
      }

      Button('Reset')
        .onClick(() => {
          this.clickCount = 0;
          this.lastStatus = 'Ready';
          this.flag = true;
        })

      Column({ space: 10 }) {
        Text('Reproduction Conditions:')
          .fontSize(14)
          .fontWeight(FontWeight.Bold)
        
        Text('1. resizable interface must be set')
          .fontSize(12)
          .fontColor('#666666')
        
        Text('2. Component rebuild via if condition')
          .fontSize(12)
          .fontColor('#666666')
        
        Text('3. transition animation enabled')
          .fontSize(12)
          .fontColor('#666666')
        
        Text('4. Rapid rebuild increases probability')
          .fontSize(12)
          .fontColor('#666666')
        
        Text('5. Fixed width/height (200x200)')
          .fontSize(12)
          .fontColor('#666666')
      }
      .alignItems(HorizontalAlign.Start)
      .width('100%')
      .padding(16)
      .backgroundColor('#FAFAFA')
      .borderRadius(8)
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .justifyContent(FlexAlign.Start)
  }
}
