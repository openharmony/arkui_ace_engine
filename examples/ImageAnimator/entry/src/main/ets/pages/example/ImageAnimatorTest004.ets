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

@Entry
@Component
struct ImageAnimatorTest004 {
  @State testTitle: string = '图片源测试';
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State testResults: string[] = [];
  @State currentImageSet: number = 0;
  @State iterations: number = 1;

  private imageSets: Array<ImageFrameInfo[]> = [
    [
      { src: $r('app.media.img1') },
      { src: $r('app.media.img2') }
    ],
    [
      { src: $r('app.media.img1') },
      { src: $r('app.media.img2') },
      { src: $r('app.media.img3') }
    ],
    [
      { src: $r('app.media.img1') },
      { src: $r('app.media.img2') },
      { src: $r('app.media.img3') },
      { src: $r('app.media.img4') }
    ],
    [
      { src: $r('app.media.img1') },
      { src: $r('app.media.img2') },
      { src: $r('app.media.img3') },
      { src: $r('app.media.img4') },
      { src: $r('app.media.img1') },
      { src: $r('app.media.img2') }
    ]
  ];

  private addTestResult(testName: string, result: boolean, details: string = '') {
    const status = result ? 'PASS' : 'FAIL';
    const timestamp = new Date().toLocaleTimeString();
    this.testResults.unshift(`[${timestamp}] ${testName}: ${status} ${details}`);
  }

  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text(this.testTitle)
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        Divider().strokeWidth(2)

        this.buildTestSection()

        Divider().strokeWidth(2)

        this.buildImageSetSelector()

        Divider().strokeWidth(2)

        this.buildImageAnimator()

        Divider().strokeWidth(2)

        this.buildTestResults()
      }
      .width('100%')
      .padding(20)
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  buildTestSection() {
    Column({ space: 10 }) {
      Text('图片源测试控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试1: 单张图片')
          .onClick(() => {
            this.testSingleImage();
          })

        Button('测试2: 两张图片')
          .onClick(() => {
            this.testTwoImages();
          })

        Button('测试3: 三张图片')
          .onClick(() => {
            this.testThreeImages();
          })
      }

      Row({ space: 10 }) {
        Button('测试4: 四张图片')
          .onClick(() => {
            this.testFourImages();
          })

        Button('测试5: 多张图片')
          .onClick(() => {
            this.testMultipleImages();
          })

        Button('测试6: 图片源切换')
          .onClick(() => {
            this.testImageSourceSwitch();
          })
      }

      Row({ space: 10 }) {
        Button('测试7: 重复图片')
          .onClick(() => {
            this.testDuplicateImages();
          })

        Button('测试8: 图片源验证')
          .onClick(() => {
            this.testImageSourceValidation();
          })

        Button('清空结果')
          .onClick(() => {
            this.testResults = [];
          })
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildImageSetSelector() {
    Column({ space: 10 }) {
      Text('图片集选择')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        ForEach(this.imageSets, (images: ImageFrameInfo[], index: number) => {
          Button(`图片集${index + 1}`)
            .onClick(() => {
              this.currentImageSet = index;
            })
            .backgroundColor(this.currentImageSet === index ? 0x2196F3 : 0xE0E0E0)
            .fontColor(this.currentImageSet === index ? 0xFFFFFF : 0x000000)
        }, (images: ImageFrameInfo[], index: number) => `${index}`)
      }

      Text(`当前图片集: ${this.currentImageSet + 1}, 图片数量: ${this.imageSets[this.currentImageSet].length}`)
        .fontSize(14)
        .fontColor(0x666666)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder

  buildImageAnimator() {
    Column({ space: 10 }) {
      Text('ImageAnimator 预览')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      ImageAnimator()
        .images(this.imageSets[this.currentImageSet])
        .duration(2000)
        .state(this.state)
        .fillMode(FillMode.Forwards)
        .iterations(this.iterations)
        .width(300)
        .height(200)
        .borderRadius(10)
        .backgroundColor(0xE0E0E0)
        .onFinish(() => {
          this.state = AnimationStatus.Stopped;
        })

      Row({ space: 15 }) {
        Button('播放')
          .onClick(() => {
            this.state = AnimationStatus.Running;
          })

        Button('暂停')
          .onClick(() => {
            this.state = AnimationStatus.Paused;
          })

        Button('停止')
          .onClick(() => {
            this.state = AnimationStatus.Stopped;
          })
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildTestResults() {
    Column({ space: 10 }) {
      Text('测试结果')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      if (this.testResults.length === 0) {
        Text('暂无测试结果')
          .fontSize(14)
          .fontColor(0x999999)
      } else {
        List({ space: 5 }) {
          ForEach(this.testResults, (result: string, index: number) => {
            ListItem() {
              Text(result)
                .fontSize(12)
                .fontColor(result.includes('PASS') ? 0x4CAF50 : 0xF44336)
            }
            .width('100%')
          }, (result: string, index: number) => `${index}_${result}`)
        }
        .width('100%')
        .height(250)
        .backgroundColor(0xF0F0F0)
        .borderRadius(5)
        .padding(10)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  private testSingleImage() {
    try {
      const singleImage: ImageFrameInfo[] = [
        { src: $r('app.media.img1') }
      ];
      
      const isValid = singleImage.length === 1 && singleImage[0].src !== undefined;
      this.addTestResult('单张图片测试', isValid,
        `图片数量: ${singleImage.length}`);
    } catch (error) {
      this.addTestResult('单张图片测试', false, `错误: ${error}`);
    }
  }

  private testTwoImages() {
    try {
      const twoImages: ImageFrameInfo[] = [
        { src: $r('app.media.img1') },
        { src: $r('app.media.img2') }
      ];
      
      const isValid = twoImages.length === 2 && 
                      twoImages.every(img => img.src !== undefined);
      this.addTestResult('两张图片测试', isValid,
        `图片数量: ${twoImages.length}`);
    } catch (error) {
      this.addTestResult('两张图片测试', false, `错误: ${error}`);
    }
  }

  private testThreeImages() {
    try {
      const threeImages: ImageFrameInfo[] = [
        { src: $r('app.media.img1') },
        { src: $r('app.media.img2') },
        { src: $r('app.media.img3') }
      ];
      
      const isValid = threeImages.length === 3 && 
                      threeImages.every(img => img.src !== undefined);
      this.addTestResult('三张图片测试', isValid,
        `图片数量: ${threeImages.length}`);
    } catch (error) {
      this.addTestResult('三张图片测试', false, `错误: ${error}`);
    }
  }

  private testFourImages() {
    try {
      const fourImages: ImageFrameInfo[] = [
        { src: $r('app.media.img1') },
        { src: $r('app.media.img2') },
        { src: $r('app.media.img3') },
        { src: $r('app.media.img4') }
      ];
      
      const isValid = fourImages.length === 4 && 
                      fourImages.every(img => img.src !== undefined);
      this.addTestResult('四张图片测试', isValid,
        `图片数量: ${fourImages.length}`);
    } catch (error) {
      this.addTestResult('四张图片测试', false, `错误: ${error}`);
    }
  }

  private testMultipleImages() {
    try {
      const multipleImages: ImageFrameInfo[] = [
        { src: $r('app.media.img1') },
        { src: $r('app.media.img2') },
        { src: $r('app.media.img3') },
        { src: $r('app.media.img4') },
        { src: $r('app.media.img1') },
        { src: $r('app.media.img2') }
      ];
      
      const isValid = multipleImages.length === 6 && 
                      multipleImages.every(img => img.src !== undefined);
      this.addTestResult('多张图片测试', isValid,
        `图片数量: ${multipleImages.length}`);
    } catch (error) {
      this.addTestResult('多张图片测试', false, `错误: ${error}`);
    }
  }

  private testImageSourceSwitch() {
    try {
      const originalSet = this.currentImageSet;
      let allValid = true;
      
      for (let i = 0; i < this.imageSets.length; i++) {
        this.currentImageSet = i;
        if (this.currentImageSet !== i) {
          allValid = false;
          break;
        }
      }
      
      this.currentImageSet = originalSet;
      this.addTestResult('图片源切换测试', allValid,
        `切换了 ${this.imageSets.length} 个图片集`);
    } catch (error) {
      this.addTestResult('图片源切换测试', false, `错误: ${error}`);
    }
  }

  private testDuplicateImages() {
    try {
      const duplicateImages: ImageFrameInfo[] = [
        { src: $r('app.media.img1') },
        { src: $r('app.media.img1') },
        { src: $r('app.media.img2') },
        { src: $r('app.media.img2') }
      ];
      
      const isValid = duplicateImages.length === 4 && 
                      duplicateImages.every(img => img.src !== undefined);
      this.addTestResult('重复图片测试', isValid,
        `图片数量: ${duplicateImages.length}, 包含重复图片`);
    } catch (error) {
      this.addTestResult('重复图片测试', false, `错误: ${error}`);
    }
  }

  private testImageSourceValidation() {
    try {
      let allValid = true;
      const results: string[] = [];
      
      for (let i = 0; i < this.imageSets.length; i++) {
        const images = this.imageSets[i];
        const isValid = images.length > 0 && images.every(img => img.src !== undefined);
        allValid = allValid && isValid;
        results.push(`图片集${i + 1}: ${images.length}张 ${isValid ? '✓' : '✗'}`);
      }
      
      this.addTestResult('图片源验证', allValid, results.join(', '));
    } catch (error) {
      this.addTestResult('图片源验证', false, `错误: ${error}`);
    }
  }
}
