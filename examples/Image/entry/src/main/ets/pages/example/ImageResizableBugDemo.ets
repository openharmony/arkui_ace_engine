/**
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * Image Resizable Bug Demo
 * 
 * This demo reproduces the bug where using resizable interface with animated images
 * can result in dstRect being 0, causing the image not to display.
 * 
 * Root Cause Analysis:
 * 
 * Bug Scenario 1: Animation timing issue
 * - Animated GIF starts loading
 * - During animation playback, a layout re-measure is triggered
 * - If GetContent() returns null before layout completes, StartDecoding returns early
 * - MakeCanvasImageIfNeed is not called
 * - dstRect_ remains 0 (default value)
 * 
 * Bug Scenario 2: Resizable interface special handling
 * - Image with resizable slice is loaded successfully
 * - During animation, a new MakeCanvasImage request arrives
 * - hasValidSlice is true, but other parameters unchanged
 * - !res is true in MakeCanvasImageIfNeed (line 338-340)
 * - Only dstSize_ is updated, dstRect_ is NOT recalculated
 * - If dstRect_ was reset to 0 somehow, image won't display
 * 
 * Bug Scenario 3: Component visibility toggle
 * - Component is hidden during image load
 * - Component becomes visible (with animation)
 * - GetContentSize() may return 0 during transition
 * - dstRect calculated as 0
 */

@Entry
@Component
struct ImageResizableBugDemo {
  @State private isVisible: boolean = false;
  @State private showImage: boolean = true; // 用于强制重建图片
  @State private animationTrigger: number = 0;
  @State private imageWidth: number = 200;
  @State private imageHeight: number = 200;
  @State private reloadCount: number = 0;
  @State private lastLogTime: number = 0;

  build() {
    Column() {
      Row() {
        Button('Toggle Visibility')
          .onClick(() => {
            this.toggleVisibility();
          })
        Button('Trigger Animation')
          .onClick(() => {
            this.triggerAnimation();
          })
      }
      .margin({ bottom: 10 })

      Row() {
        Button('Reload Image')
          .onClick(() => {
            this.reloadImage();
          })
        Button('🔄 Rebuild Image')
          .onClick(() => {
            this.rebuildImage();
          })
          .backgroundColor('#FF6B6B')
      }
      .margin({ bottom: 10 })

      // Image with resizable and animation
      if (this.isVisible && this.showImage) {
        Image($r('app.media.example'))
          .width(this.imageWidth)
          .height(this.imageHeight)
          .resizable({ slice: { top: 10, bottom: 10, left: 10, right: 10 } })
          .objectFit(ImageFit.Cover)
          .opacity(this.animationTrigger > 0 ? 1.0 : 0.0)
          .animationDuration(1000)
          .onComplete(() => {
            console.log('[ImageResizableBugDemo] Image loaded');
            this.logEvent('Image loaded');
          })
          .onError((error) => {
            console.error('[ImageResizableBugDemo] Image error:', error);
            this.logEvent(`Image error: ${error}`);
          })
      }

      // Debug info
      Text(`Visibility: ${this.isVisible}`)
        .margin({ top: 10 })
      Text(`Animation Trigger: ${this.animationTrigger}`)
        .margin({ top: 30 })
      Text(`Reload Count: ${this.reloadCount}`)
        .margin({ top: 50 })
      Text(`Image Size: ${this.imageWidth}x${this.imageHeight}`)
        .margin({ top: 70 })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
  }

  private toggleVisibility() {
    this.isVisible = !this.isVisible;
    this.logEvent(`Visibility toggled to: ${this.isVisible}`);
    
    // Bug Scenario 1: Rapid visibility toggle during image loading
    // This can cause GetContent() to be null when StartDecoding is called
    if (this.isVisible && this.animationTrigger === 0) {
      setTimeout(() => {
        this.animationTrigger = 1;
        this.logEvent('Animation triggered after visibility toggle');
      }, 100); // Short delay to create race condition
    }
  }

  private triggerAnimation() {
    // Bug Scenario 2: Trigger animation while resizable is active
    // This can cause dstRect not being recalculated in MakeCanvasImageIfNeed
    this.animationTrigger = this.animationTrigger > 0 ? 0 : 1;
    this.logEvent(`Animation triggered: ${this.animationTrigger}`);
  }

  private rebuildImage() {
    // Force rebuild image by toggling showImage flag rapidly
    // This creates a race condition that can trigger the dstRect=0 bug
    this.logEvent('=== Rebuild Image Start ===');
    
    // Step 1: Hide image (destroy component)
    this.showImage = false;
    this.logEvent('Step 1: Image destroyed (showImage=false)');
    
    // Step 2: Wait and recreate (creates race condition)
    setTimeout(() => {
      this.showImage = true;
      this.logEvent('Step 2: Image recreated (showImage=true)');
      
      // Step 3: Trigger animation during layout phase
      setTimeout(() => {
        this.animationTrigger = 1;
        this.logEvent('Step 3: Animation triggered during layout');
        
        // Step 4: Change size rapidly (creates dstRect=0 condition)
        setTimeout(() => {
          const oldWidth = this.imageWidth;
          this.imageWidth = this.imageWidth === 200 ? 250 : 200;
          this.imageHeight = this.imageHeight === 200 ? 250 : 200;
          this.logEvent(`Step 4: Size changed from ${oldWidth}x${oldWidth} to ${this.imageWidth}x${this.imageHeight}`);
          
          // Step 5: Toggle animation rapidly to increase probability
          setTimeout(() => {
            this.animationTrigger = 0;
            this.logEvent('Step 5: Animation toggled off');
            
            setTimeout(() => {
              this.animationTrigger = 1;
              this.reloadCount++;
              this.logEvent(`Step 6: Animation toggled on - Bug should reproduce! (Count: ${this.reloadCount})`);
            }, 50);
          }, 100);
        }, 150);
      }, 100);
    }, 200);
  }

  private reloadImage() {
    // Bug Scenario 3: Reload image with different size
    // This can cause layout re-measure and potential dstRect calculation issues
    this.reloadCount++;
    this.imageWidth = this.imageWidth === 200 ? 300 : 200;
    this.imageHeight = this.imageHeight === 200 ? 300 : 200;
    this.animationTrigger = 0;
    this.logEvent(`Image reloaded with size: ${this.imageWidth}x${this.imageHeight}`);
  }

  private logEvent(message: string) {
    const now = Date.now();
    const elapsed = this.lastLogTime > 0 ? now.getTime() - this.lastLogTime : 0;
    console.log(`[${now.toISOString()}] [ImageResizableBugDemo] ${message} ${elapsed > 0 ? `(${elapsed}ms since last)` : ''}`);
    this.lastLogTime = now.getTime();
  }
}
