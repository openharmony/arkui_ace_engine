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
 * Static Image with Resizable Bug Demo
 * 
 * This demo reproduces the bug where static images with resizable interface
 * can fail to display due to dstRect being 0 during rapid layout changes.
 * 
 * Root Cause Analysis:
 * 
 * Bug Scenario: Layout timing issue with resizable
 * 
 * Detailed Flow:
 * 1. Image starts loading with resizable slice set
 * 2. OnImageDataReady() is called when image data is loaded
 * 3. CheckIfNeedLayout() determines if layout is needed
 * 4. During rapid layout changes, GetContent() may be null
 * 5. StartDecoding(GetContentSize()) is called
 * 6. GetContent() returns null (layout not finished)
 * 7. StartDecoding() returns early without calling MakeCanvasImageIfNeed
 * 8. dstRect_ remains default value (0, 0, 0, 0)
 * 9. DrawToRSCanvas receives dstRect with size 0
 * 10. Image doesn't display
 * 
 * Key Code Locations:
 * - image_pattern.cpp:717-719: GetContent() null check
 * - image_pattern.cpp:741: MakeCanvasImageIfNeed call
 * - image_loading_context.cpp:90: dstRect_ = RectF()
 * - pixelmap_image.cpp:320: DrawToRSCanvas receives dstRect
 */

@Entry
@Component
struct StaticImageResizableBugDemo {
  @State private imageSrc: Resource = $r('app.media.example'); // Local static image
  @State private showImage: boolean = true; // 用于强制重建图片
  @State private imageFit: ImageFit = ImageFit.Cover;
  @State private containerWidth: number = 300;
  @State private containerHeight: number = 300;
  @State private sliceTop: number = 10;
  @State private sliceBottom: number = 10;
  @State private sliceLeft: number = 10;
  @State private sliceRight: number = 10;
  @State private iterationCount: number = 0;
  @State private testResults: string[] = [];

  build() {
    Column() {
      // Test controls
      Row() {
        Button('Test: Rapid Layout Change')
          .onClick(() => {
            this.testRapidLayoutChange();
          })

        Button('Test: Toggle ImageFit')
          .onClick(() => {
            this.toggleImageFit();
          })
      }
      .margin({ bottom: 10 })

      Row() {
        Button('Test: Change Slice')
          .onClick(() => {
            this.changeSlice();
          })

        Button('🔄 Rebuild Image')
          .onClick(() => {
            this.rebuildImage();
          })
          .backgroundColor('#FF6B6B')
      }
      .margin({ bottom: 10 })

      // Static image with resizable
      Column() {
        if (this.showImage) {
          Image(this.imageSrc)
            .width(this.containerWidth)
            .height(this.containerHeight)
            .resizable({ slice: { top: this.sliceTop, bottom: this.sliceBottom, left: this.sliceLeft, right: this.sliceRight } })
            .objectFit(this.imageFit)
            .onComplete(() => {
              this.addTestResult('Image loaded successfully');
            })
            .onError((error) => {
              this.addTestResult(`Image load error: ${error.message}`);
            })
        }

        // Debug overlay
        Text(`Iteration: ${this.iterationCount}`)
          .fontSize(12)
          .fontColor(Color.White)
          .backgroundColor('#66000000')
      }
      .width(this.containerWidth)
      .height(this.containerHeight)
      .backgroundColor('#F0F0F0')
      .justifyContent(FlexAlign.Center)
      .alignItems(HorizontalAlign.Center)

      // Test results log
      Scroll() {
        Column() {
          ForEach(this.testResults, (result: string, index: number) => {
            Text(result)
              .fontSize(12)
              .width('100%')
              .padding(5)
              .backgroundColor(index % 2 === 0 ? '#E0E0E0' : '#F5F5F5')
          })
        }
      }
      .width('100%')
      .height(200)
      .backgroundColor('#EEEEEE')
      .margin({ top: 20 })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Start)
    .alignItems(HorizontalAlign.Center)
    .padding(20)
  }

  /**
   * Bug Scenario 1: Rapid layout change during animation
   * 
   * This triggers the bug by:
   * 1. Starting GIF animation
   * 2. Immediately changing container size (triggers layout)
   * 3. If GetContent() is null during layout, StartDecoding returns early
   * 4. dstRect_ remains 0
   */
  private testRapidLayoutChange() {
    this.iterationCount++;
    this.addTestResult(`=== Test ${this.iterationCount}: Rapid Layout Change ===`);
    
    // Step 1: Load image
    this.containerWidth = 300;
    this.containerHeight = 300;
    this.addTestResult('Initial container size: 300x300');
    
    // Step 2: Wait for animation to start, then trigger layout
    setTimeout(() => {
      this.addTestResult('Changing container size to trigger layout...');
      this.containerWidth = 200;
      this.containerHeight = 200;
      this.addTestResult('Container size changed to 200x200');
      
      // Step 3: Change again quickly to create race condition
      setTimeout(() => {
        this.containerWidth = 350;
        this.containerHeight = 350;
        this.addTestResult('Container size changed to 350x350 (race condition)');
      }, 50); // Very short delay to create timing issue
    }, 500); // Wait for animation to potentially start
  }

  /**
   * Bug Scenario 2: Toggle ImageFit during animation
   * 
   * This can trigger the bug in MakeCanvasImageIfNeed where:
   * - hasValidSlice is true
   * - ImageFit changes
   * - MakeCanvasImageIfNeed is called
   * - If GetContentSize() returns 0 during transition, dstRect becomes 0
   */
  private toggleImageFit() {
    this.iterationCount++;
    this.addTestResult(`=== Test ${this.iterationCount}: Toggle ImageFit ===`);
    
    const fits: ImageFit[] = [
      ImageFit.Cover,
      ImageFit.Contain,
      ImageFit.Fill,
      ImageFit.ScaleDown
    ];
    
    const currentIndex = fits.indexOf(this.imageFit);
    const nextIndex = (currentIndex + 1) % fits.length;
    this.imageFit = fits[nextIndex];
    
    this.addTestResult(`ImageFit changed to: ${this.imageFit}`);
    this.addTestResult('This may trigger MakeCanvasImageIfNeed with hasValidSlice=true');
  }

  /**
   * Bug Scenario 3: Change resizable slice during animation
   * 
   * This can trigger the bug in image_loading_context.cpp:338-340 where:
   * - hasValidSlice is true
   * - Other parameters don't change (!res is true)
   * - Only dstSize_ is updated, dstRect_ is NOT recalculated
   * - If dstRect_ was 0, it stays 0
   */
  private changeSlice() {
    this.iterationCount++;
    this.addTestResult(`=== Test ${this.iterationCount}: Change Slice ===`);
    
    const slices = [10, 20, 30, 5];
    const currentIndex = slices.indexOf(this.sliceTop);
    const nextIndex = (currentIndex + 1) % slices.length;
    
    this.sliceTop = slices[nextIndex];
    this.sliceBottom = slices[nextIndex];
    this.sliceLeft = slices[nextIndex];
    this.sliceRight = slices[nextIndex];
    
    this.addTestResult(`Slice changed to: ${this.sliceTop}`);
    this.addTestResult('This triggers MakeCanvasImageIfNeed with hasValidSlice=true');
    this.addTestResult('Bug: dstRect may not be recalculated if !res && hasValidSlice');
  }

  /**
   * Bug Scenario 4: Force rebuild image by toggling showImage flag
   * 
   * This triggers the bug by:
   * 1. Destroying image component (showImage=false)
   * 2. Recreating image component (showImage=true)
   * 3. Immediately changing layout size
   * 4. If GetContent() is null during layout, StartDecoding returns early
   * 5. dstRect_ remains 0
   */
  private rebuildImage() {
    this.iterationCount++;
    this.addTestResult(`=== Test ${this.iterationCount}: Rebuild Image ===`);
    
    // Step 1: Destroy image component
    this.showImage = false;
    this.addTestResult('Step 1: Image destroyed (showImage=false)');
    
    // Step 2: Wait and recreate with size change (creates race condition)
    setTimeout(() => {
      this.showImage = true;
      this.addTestResult('Step 2: Image recreated (showImage=true)');
      
      // Step 3: Immediately change size during recreation
      setTimeout(() => {
        const oldWidth = this.containerWidth;
        this.containerWidth = this.containerWidth === 300 ? 400 : 300;
        this.containerHeight = this.containerHeight === 300 ? 400 : 300;
        this.addTestResult(`Step 3: Size changed ${oldWidth}x${oldWidth} -> ${this.containerWidth}x${this.containerHeight}`);
        
        // Step 4: Rapid size changes to trigger race condition
        setTimeout(() => {
          this.containerWidth = 350;
          this.containerHeight = 350;
          this.addTestResult('Step 4: Size changed to 350x350 (race condition)');
          
          setTimeout(() => {
            this.containerWidth = 250;
            this.containerHeight = 250;
            this.addTestResult('Step 5: Size changed to 250x250 - Bug should reproduce!');
          }, 50);
        }, 100);
      }, 100);
    }, 200);
  }

  private addTestResult(message: string) {
    const timestamp = new Date().toISOString();
    const logMessage = `[${timestamp}] ${message}`;
    this.testResults.push(logMessage);
    
    // Keep only last 20 results
    if (this.testResults.length > 20) {
      this.testResults.shift();
    }
    
    console.log(`[AnimatedGifResizableBugDemo] ${message}`);
  }
}
