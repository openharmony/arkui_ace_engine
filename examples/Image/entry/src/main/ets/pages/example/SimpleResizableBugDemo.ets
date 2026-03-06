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
 * Simple Resizable Bug Demo
 * 
 * This demo provides a simple test case to directly trigger the bug
 * by forcing the specific conditions where dstRect becomes 0.
 */

@Entry
@Component
struct SimpleResizableBugDemo {
  @State private imageSrc: string = 'https://example.com/image.png';
  @State private showImage: boolean = false;
  @State private containerSize: number = 100;
  @State private iterationCount: number = 0;

  build() {
    Column() {
 Button('Test: Toggle Visibility')
          .onClick(() => {
            this.showImage = !this.showImage;
          })
          .margin({ top: 10 })

        Button('Test: Rapid Size Change')
          .onClick(() => {
            this.containerSize = Math.random() * 100 + 50;
            this.addLog(`Iteration ${this.iterationCount}: Container size changed to ${this.containerSize}`);
          })
          .margin({ top: 10 })

        Button('🔄 Rebuild Image')
          .onClick(() => {
            this.rebuildImage();
          })
          .backgroundColor('#FF6B6B')
          .margin({ top: 10 })

      if (this.showImage) {
        Image(this.imageSrc)
          .width(this.containerSize)
          .height(this.containerSize)
          .resizable({ slice: { top: 10, bottom: 10, left: 10, right: 10 } })
          .objectFit(ImageFit.Cover)
          .onComplete(() => {
            this.addLog('Image loaded successfully');
          })
          .onError((error) => {
            this.addLog(`Image error: ${error.message}`);
          })
      }

      Text(`Show Image: ${this.showImage}`)
        .fontSize(16)
        .margin({ top: 10 })

      Text(`Container Size: ${this.containerSize}x${this.containerSize}`)
        .fontSize(14)
        .margin({ top: 5 })

      Text(`Iterations: ${this.iterationCount}`)
        .fontSize(14)
        .margin({ top: 5 })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

      Button('Test: Rapid Size Change')
        .onClick(() => {
          this.containerSize = Math.random() * 100 + 50;
          this.addLog(`Iteration ${this.iterationCount}: Container size changed to ${this.containerSize}`);
        })

      Text(`Show Image: ${this.showImage}`)
        .fontSize(16)
        .margin({ top: 10 })

      Text(`Container Size: ${this.containerSize}x${this.containerSize}`)
        .fontSize(14)
        .margin({ top: 5 })

      Text(`Iterations: ${this.iterationCount}`)
        .fontSize(14)
        .margin({ top: 5 })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  private addLog(message: string) {
    const timestamp = new Date().toISOString();
    console.log(`[SimpleResizableBugDemo] ${message}`);
  }

  private rebuildImage() {
    this.iterationCount++;
    this.addLog(`=== Test ${this.iterationCount}: Rebuild Image ===`);
    
    // Force rebuild by toggling showImage flag
    this.showImage = false;
    this.addLog('Step 1: Image destroyed (showImage=false)');
    
    // Wait and recreate
    setTimeout(() => {
      this.showImage = true;
      this.addLog('Step 2: Image recreated (showImage=true)');
      
      // Trigger size change during recreation
      setTimeout(() => {
        this.containerSize = Math.random() * 100 + 50;
        this.addLog(`Step 3: Size changed to ${this.containerSize}`);
        
        // Change size again
        setTimeout(() => {
          this.containerSize = Math.random() * 100 + 50;
          this.addLog(`Step 4: Size changed to ${this.containerSize} - Bug should reproduce!`);
        }, 100);
      }, 100);
    }, 200);
  }
}
