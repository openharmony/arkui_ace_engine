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

import { image } from '@kit.ImageKit';
import { matrix4 } from '@kit.ArkGraphics2D';

/**
 * Image 实际应用场景示例
 * 演示 Image 组件在实际应用中的使用场景
 */
@Entry
@Component
struct ImageRealWorldExample {
  @State currentScene: number = 0;
  @State userProfileImage: PixelMap | undefined = undefined;
  @State productImages: string[] = [];
  @State bannerImages: string[] = [];
  @State avatarImage: string = '';
  @State loadingImages: {[key: string]: boolean} = {};
  @State showImageInfo: boolean = false;
  @State currentImageIndex: number = 0;
  @State imageInfo: string = '';

  scenes: string[] = [
    '用户头像',
    '产品列表',
    '广告轮播',
    '相图浏览',
    '社交动态',
    '新闻卡片'
  ];

  aboutToAppear() {
    this.initMockData();
    this.loadUserProfileImage();
  }

  initMockData() {
    this.productImages = [
      'https://xxx',
      'https://xxx',
      'https://xxx',
      'https://xxx',
      'https://xxx',
      'https://xxx',
    ];

    this.bannerImages = [
      'https://xxx',
      'https://xxx',
      'https://xxx',
    ];

    this.avatarImage = 'https://xxx',;
  }

  async loadUserProfileImage() {
    try {
      const resManager = this.getUIContext().getHostContext()?.resourceManager;
      if (!resManager) {
        return;
      }

      const unit8Array = await resManager.getMediaContent($r('app.media.img').id);
      if (!unit8Array) {
        return;
      }

      const imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength));
      const pixelMap = await imageSource.createPixelMap({
        desiredPixelFormat: image.PixelMapFormat.RGBA_8888
      });
      await imageSource.release();

      this.userProfileImage = pixelMap;
    } catch (error) {
      console.error(`加载用户头像失败: ${error}`);
    }
  }

  @Builder
  UserProfileScene() {
    Column({ space: 20 }) {
      Text('用户头像场景')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      // 用户信息卡片
      Row({ space: 20 }) {
        // 头像
        Column({ space: 10 }) {
          if (this.userProfileImage) {
            Image(this.userProfileImage)
              .width(100)
              .height(100)
              .borderRadius(50)
              .border({ width: 3, color: Color.Blue })
              .objectFit(ImageFit.Cover)
              .shadow({ radius: 10, color: 0x1A000000, offsetX: 0, offsetY: 5 })
          } else {
            Image($r('app.media.placeholder'))
              .width(100)
              .height(100)
              .borderRadius(50)
              .backgroundColor(0xE0E0E0)
          }

          Text('用户名')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .textAlign(TextAlign.Center)
            .width('100%')

          Text('用户签名或简介')
            .fontSize(12)
            .fontColor(0x666666)
            .textAlign(TextAlign.Center)
            .maxLines(2)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .width('100%')
        }

        // 用户详细信息
        Column({ space: 15 }) {
          Text('用户详细信息')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)

          Column({ space: 10 }) {
            Text('性别')
              .fontSize(14)
              .fontColor(0x666666)
            Text('男')
              .fontSize(16)
              .fontWeight(FontWeight.Medium)
          }

          Column({ space: 10 }) {
            Text('年龄')
              .fontSize(14)
              .fontColor(0x666666)
            Text('28岁')
              .fontSize(16)
              .fontWeight(FontWeight.Medium)
          }

          Column({ space: 10 }) {
            Text('职业')
              .fontSize(14)
              .fontColor(0x666666)
            Text('软件工程师')
              .fontSize(16)
              .fontWeight(FontWeight.Medium)
          }

          Column({ space: 10 }) {
            Text('所在地')
              .fontSize(14)
              .fontColor(0x666666)
            Text('北京市')
              .fontSize(16)
              .fontWeight(FontWeight.Medium)
          }

          Row({ space: 15 }) {
            Button('关注')
              .type(ButtonType.Normal)
              .backgroundColor(0x007DFF)
              .borderRadius(20)

            Button('私信')
              .type(ButtonType.Normal)
              .backgroundColor(0xF5F5F5)
              .borderRadius(20)

            Button('更多')
              .type(ButtonType.Normal)
              .backgroundColor(0xE0E0E0)
              .borderRadius(20)
          }
        }
        .layoutWeight(1)
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)
        .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })
      }
      .width('100%')
      .padding(20)
      .backgroundColor(0xF5F5F5)
      .borderRadius(15)
    }
    .padding(20)
  }

  @Builder
  ProductListScene() {
    Column({ space: 20 }) {
      Text('产品列表场景')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      // 产品网格
      Grid() {
        ForEach(this.productImages, (url: string, index: number) => {
          GridItem() {
            Column({ space: 10 }) {
              // 产品图片
              Stack({ alignContent: Alignment.TopEnd }) {
                Image(url)
                  .width('100%')
                  .aspectRatio(1)
                  .borderRadius(10)
                  .objectFit(ImageFit.Cover)
                  .alt($r('app.media.placeholder'))
                  .onComplete((event) => {
                    this.loadingImages[url] = false;
                    console.info(`产品图片 ${index + 1} 加载成功`);
                  })
                  .onError((error) => {
                    console.error(`产品图片 ${index + 1} 加载失败: ${error.message}`);
                  })

                // 价格标签
                Text(`¥${(index + 1) * 100}`)
                  .fontSize(14)
                  .fontWeight(FontWeight.Bold)
                  .fontColor(Color.White)
                  .padding({ left: 10, right: 10, top: 5, bottom: 5 })
                  .backgroundColor(0xFF5252)
                  .borderRadius({ bottomLeft: 10 })
              }
              .borderRadius(10)
              .shadow({ radius: 6, color: 0x1A000000, offsetX: 0, offsetY: 2 })

              // 产品信息
              Column({ space: 5 }) {
                Text(`产品 ${index + 1}`)
                  .fontSize(14)
                  .fontWeight(FontWeight.Medium)
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })

                Text('产品描述文字，展示产品的主要特点。')
                  .fontSize(12)
                  .fontColor(0x666666)
                  .maxLines(2)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .lineHeight(16)
              }
            }
            .padding(10)
            .backgroundColor(0xFFFFFF)
            .borderRadius(10)
          }
        })
      }
      .columnsTemplate('1fr 1fr 1fr')
      .rowsGap(15)
      .columnsGap(15)
      .padding(15)
    }
    .padding(20)
  }

  @Builder
  BannerCarouselScene() {
    Column({ space: 20 }) {
      Text('广告轮播场景')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      // 轮播图容器
      Swiper() {
        ForEach(this.bannerImages, (url: string, index: number) => {
          SwiperItem() {
            Stack({ alignContent: Alignment.BottomStart }) {
              // 轮播图片
              Image(url)
                .width('100%')
                .height(400)
                .objectFit(ImageFit.Cover)
                .alt($r('app.media.placeholder'))
                .onComplete((event) => {
                  console.info(`轮播图 ${index + 1} 加载成功: ${event.width}x${event.height}`);
                })
                .onError((error) => {
                  console.error(`轮播图 ${index + 1} 加载失败: ${error.message}`);
                })

              // 文字覆盖层
              Column({ space: 5 }) {
                Text(`广告 ${index + 1}`)
                  .fontSize(24)
                  .fontWeight(FontWeight.Bold)
                  .fontColor(Color.White)

                Text('这是广告的描述文字，展示广告的主要内容。')
                  .fontSize(16)
                  .fontColor(0xF0F0F0)
                  .maxLines(2)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
              }
              .padding(20)
              .width('100%')
              .backgroundColor('rgba(0, 0, 0, 0.5)')
            }
          }
        })
      }
      .width('100%')
      .height(400)
      .loop(true)
      .autoPlay(true)
      .interval(3000)
      .indicator(true)
      .borderRadius(15)
      .shadow({ radius: 10, color: 0x1A000000, offsetX: 0, offsetY: 5 })
    }
    .padding(20)
  }

  @Builder
  PhotoGalleryScene() {
    Column({ space: 20 }) {
      Text('相图浏览场景')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      // 相图网格
      Grid() {
        ForEach(Array.from({ length: 12 }), (_: number, index: number) => {
          GridItem() {
            Stack({ alignContent: Alignment.TopEnd }) {
              Image($r('app.media.img'))
                .width('100%')
                .aspectRatio(1)
                .borderRadius(8)
                .objectFit(ImageFit.Cover)
                .onClick(() => {
                  this.currentImageIndex = index;
                  this.showImageInfo = true;
                  this.imageInfo = `相图 ${index + 1}`;
                })

              if (this.showImageInfo && this.currentImageIndex === index) {
                // 选中标记
                Column() {
                  Text('✓')
                    .fontSize(24)
                    .fontColor(Color.White)
                }
                .width(30)
                .height(30)
                .backgroundColor(0x007DFF)
                .borderRadius(15)
                .margin(5)
              }
            }
            .borderRadius(8)
            .shadow({ radius: 4, color: 0x1A000000, offsetX: 0, offsetY: 2 })
          }
        })
      }
      .columnsTemplate('1fr 1fr 1fr 1fr')
      .rowsGap(10)
      .columnsGap(10)
      .padding(15)
    }

      // 图片信息面板
      if (this.showImageInfo) {
        Column({ space: 10 }) {
          Text(this.imageInfo)
            .fontSize(18)
            .fontWeight(FontWeight.Bold)

          Row({ space: 15 }) {
            Button('设为头像')
              .type(ButtonType.Normal)
              .backgroundColor(0x007DFF)
              .borderRadius(20)

            Button('分享')
              .type(ButtonType.Normal)
              .backgroundColor(0xF5F5F5)
              .borderRadius(20)

            Button('删除')
              .type(ButtonType.Normal)
              .backgroundColor(0xFF5252)
              .borderRadius(20)
              .onClick(() => {
                this.showImageInfo = false;
              })
          }
        }
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)
        .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })
      }
    }
    .padding(20)
  }

  @Builder
  SocialFeedScene() {
    Column({ space: 20 }) {
      Text('社交动态场景')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      ForEach([1, 2, 3], (item: number) => {
        Column({ space: 15 }) {
          // 用户信息
          Row({ space: 15 }) {
            // 头像
            Image($this.avatarImage)
              .width(50)
              .height(50)
              .borderRadius(25)
              .objectFit(ImageFit.Cover)
              .border({ width: 2, color: Color.Blue })

            // 用户名和时间
            Column({ space: 5 }) {
              Text(`用户 ${item}`)
                .fontSize(16)
                .fontWeight(FontWeight.Bold)

              Text('2小时前')
                .fontSize(12)
                .fontColor(0x999999)
            }
            .layoutWeight(1)
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFFF)
          .borderRadius(10)

          // 动态内容
          Column({ space: 10 }) {
            Text('这是用户发布的动态内容，可以包含文字描述。')
              .fontSize(14)
              .lineHeight(20)

            // 动态图片
            Image($r('app.media.jpg'))
              .width('100%')
              .height(300)
              .borderRadius(10)
              .objectFit(ImageFit.Cover)
              .margin({ top: 10 })
          }
          .padding(15)
          .backgroundColor(0xF9F9F9)
          .borderRadius(10)

          // 互动按钮
          Row({ space: 20 }) {
            Row({ space: 5 }) {
              Text('👍')
                .fontSize(20)
              Text('点赞')
                .fontSize(14)
                .fontColor(0x666666)
            }
            .onClick(() => {
              console.info(`点赞动态 ${item}`);
            })

            Row({ space: 5 }) {
              Text('💬')
                .fontSize(20)
              Text('评论')
                .fontSize(14)
                .fontColor(0x666666)
            }

            Row({ space: 5 }) {
              Text('🔄')
                .fontSize(20)
              Text('分享')
                .fontSize(14)
                .fontColor(0x666666)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFFF)
          .borderRadius({ bottomLeft: 10, bottomRight: 10 })
        }
        .width('100%')
        .margin({ bottom: 20 })
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)
        .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })
      })
    }
    .padding(20)
  }

  @Builder
  NewsCardScene() {
    Column({ space: 20 }) {
      Text('新闻卡片场景')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      ForEach([1, 2], (item: number) => {
        Column({ space: 15 }) {
          // 新闻图片
          Image($r('app.media.png'))
            .width('100%')
            .height(250)
            .borderRadius({ topLeft: 10, topRight: 10 })
            .objectFit(ImageFit.Cover)

          // 新闻内容
          Column({ space: 10 }) {
            Text(`新闻标题 ${item}`)
              .fontSize(20)
              .fontWeight(FontWeight.Bold)
              .maxLines(2)
              .textOverflow({ overflow: TextOverflow.Ellipsis })

            Row({ space: 15 }) {
              Text('2024-01-15')
                .fontSize(12)
                .fontColor(0x999999)

              Text('来源')
                .fontSize(12)
                .fontColor(0x666666)

              Text('阅读量: ${(item * 1000)}`)
                .fontSize(12)
                .fontColor(0x007DFF)
            }

            Text('这是新闻的摘要内容，展示新闻的主要信息。支持多行显示和文本溢出省略号。')
              .fontSize(14)
              .fontColor(0x666666)
              .lineHeight(20)
              .maxLines(3)
              .textOverflow({ overflow: TextOverflow.Ellipsis })

            Row({ space: 15 }) {
              Button('阅读全文')
                .type(ButtonType.Normal)
                .backgroundColor(0x007DFF)
                .borderRadius(20)

              Button('收藏')
                .type(ButtonType.Normal)
                .backgroundColor(0xF5F5F5)
                .borderRadius(20)

              Button('分享')
                .type(ButtonType.Normal)
                .backgroundColor(0xE0E0E0)
                .borderRadius(20)
            }
          }
          .padding(15)
          .backgroundColor(0xFFFFFF)
          .borderRadius({ bottomLeft: 10, bottomRight: 10 })
        }
        .width('100%')
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)
        .shadow({ radius: 10, color: 0x1A000000, offsetX: 0, offsetY: 4 })
        .margin({ bottom: 20 })
      })
    }
    .padding(20)
  }

  @Builder
  SceneSelector() {
    Column({ space: 15 }) {
      Text('选择场景')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      Flex({ wrap: FlexWrap.Wrap }) {
        ForEach(this.scenes, (scene: string, index: number) => {
          Button(scene)
            .type(this.currentScene === index ? ButtonType.Capsule : ButtonType.Normal)
            .fontSize(12)
            .backgroundColor(this.currentScene === index ? 0x007DFF : 0xF5F5F5)
            .margin({ right: 10, bottom: 10 })
            .onClick(() => {
              this.currentScene = index;
            })
        })
      }
    }
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
    .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })
  }

  build() {
    Column() {
      Text('Image 实际应用场景示例')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        // 左侧：场景展示
        Scroll() {
          Column({ space: 20 }) {
            if (this.currentScene === 0) {
              this.UserProfileScene()
            } else if (this.currentScene === 1) {
              this.ProductListScene()
            } else if (this.currentScene === 2) {
              this.BannerCarouselScene()
            } else if (this.currentScene === 3) {
              this.PhotoGalleryScene()
            } else if (this.currentScene === 4) {
              this.SocialFeedScene()
            } else if (this.currentScene === 5) {
              this.NewsCardScene()
            }
          }
          .padding(20)
        }
        .layoutWeight(1)
        .backgroundColor(0xFAFAFA)

        Divider()
          .vertical(true)
          .color(0xDDDDDD)
          .strokeWidth(2)

        // 右侧：场景选择
        Column({ space: 20 }) {
          this.SceneSelector()

          // 使用说明
          Column({ space: 10 }) {
            Text('使用说明')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)

            Text('1. 选择左侧场景查看效果')
              .fontSize(12)
              .fontColor(0x666666)
              .lineHeight(18)

            Text('2. 所有图片均支持加载状态监听')
              .fontSize(12)
              .fontColor(0x666666)
              .lineHeight(18)

            Text('3. 使用 objectFit 适配不同容器')
              .fontSize(12)
              .fontColor(0x666666)
              .lineHeight(18)

            Text('4. 支持网络图片和本地资源')
              .fontSize(12)
              .fontColor(0x666666)
              .lineHeight(18)
          }
          .padding(15)
          .backgroundColor(0xF0F8FF)
          .borderRadius(10)
          .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })
        }
        .)
        .padding(10)
        .backgroundColor(0xF5F5F5)
      }
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(0xF5F5F5)
  }
}
