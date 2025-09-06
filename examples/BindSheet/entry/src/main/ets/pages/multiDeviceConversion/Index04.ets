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
import { MyNodeController, createMyNode, getMyNode } from '../../NodeContainer/CustomComponent';
import { ComponentAttrUtils, RectInfoInPx } from '../../utils/ComponentAttrUtils';
import { WindowUtils } from '../../utils/WindowUtils';
import { inspector } from '@kit.ArkUI'

class AnimationInfo {
  public scale: number = 0;
  public translateX: number = 0;
  public translateY: number = 0;
  public clipWidth: Dimension = 0;
  public clipHeight: Dimension = 0;
}

@Entry
@Component
struct Index04 {
  @State isShowSheet: boolean = false;
  @State isShowImage: boolean = false;
  @State isShowOverlay: boolean = false;
  @State isAnimating: boolean = false;
  @State isEnabled: boolean = true;


  @State scaleValue: number = 0;
  @State translateX: number = 0;
  @State translateY: number = 0;
  @State clipWidth: Dimension = 0;
  @State clipHeight: Dimension = 0;
  @State radius: number = 0;
  // 原图的透明度
  @State opacityDegree: number = 1;


  // 抓取照片原位置信息
  private originInfo: AnimationInfo = new AnimationInfo;
  // 抓取照片在半模态页上位置信息
  private targetInfo: AnimationInfo = new AnimationInfo;
  // 半模态高度
  private bindSheetHeight: number = 450;
  // 半模态上图片圆角
  private sheetRadius: number = 20;

  private preferTypeArr:SheetType[] = [SheetType.BOTTOM, SheetType.CONTENT_COVER];
  private preferTypeArrStr:string[] = ['BOTTOM', 'CONTENT_COVER'];
  @State preferTypeIndex:number = 0;

  // 设置半模态上图片的布局监听
  listener:inspector.ComponentObserver = this.getUIContext().getUIInspector().createComponentObserver('target');
  aboutToAppear(): void {
    // 设置半模态上图片的布局完成回调
    let onLayoutComplete:()=>void=():void=>{
      // 目标图片布局完成时抓取布局信息
      this.targetInfo = this.calculateData('target');
      // 仅半模态正确布局且此时无动画时触发一镜到底动画
      if (this.targetInfo.scale != 0 && this.targetInfo.clipWidth != 0 &&
        this.targetInfo.clipHeight != 0 && !this.isAnimating) {
        this.isAnimating = true;
        // 用于一镜到底的模态页的属性动画
        this.getUIContext()?.animateTo({
          duration: 1000,
          curve: Curve.Friction,
          onFinish: () => {
            // 模态转场页（overlay）上的自定义节点下树
            this.isShowOverlay = false;
            // 半模态上的自定义节点上树，由此完成节点迁移
            this.isShowImage = true;
          }
        }, () => {
          this.scaleValue = this.targetInfo.scale;
          this.translateX = this.targetInfo.translateX;
          this.clipWidth = this.targetInfo.clipWidth;
          this.clipHeight = this.targetInfo.clipHeight;
          // 修正因半模态高度和缩放导致的高度差
          this.translateY = this.targetInfo.translateY +
            (this.getUIContext().px2vp(WindowUtils.windowHeightPx) - this.bindSheetHeight -
            this.getUIContext().px2vp(WindowUtils.navigationIndicatorHeightPx) -
            this.getUIContext().px2vp(WindowUtils.topAvoidAreaHeightPx));
          // 修正因缩放导致的圆角差异
          this.radius = this.sheetRadius / this.scaleValue
        })
        // 原图从透明到出现的动画
        this.getUIContext()?.animateTo({
          duration: 2000,
          curve: Curve.Friction,
        }, () => {
          this.opacityDegree = 1;
        })
      }
    }
    // 打开布局监听
    this.listener.on('layout', onLayoutComplete)
  }


  // 获取对应id的组件相对窗口左上角的属性
  calculateData(id: string): AnimationInfo {
    let itemInfo: RectInfoInPx =
      ComponentAttrUtils.getRectInfoById(WindowUtils.window.getUIContext(), id);
    // 首先计算图片的宽高与窗口宽高的比例
    let widthScaleRatio = itemInfo.width / WindowUtils.windowWidthPx;
    let heightScaleRatio = itemInfo.height / WindowUtils.windowHeightPx;
    let isUseWidthScale = widthScaleRatio > heightScaleRatio;
    let itemScale: number = isUseWidthScale ? widthScaleRatio : heightScaleRatio;
    let itemTranslateX: number = 0;
    let itemClipWidth: Dimension = 0;
    let itemClipHeight: Dimension = 0;
    let itemTranslateY: number = 0;


    if (isUseWidthScale) {
      itemTranslateX = this.getUIContext().px2vp(itemInfo.left - (WindowUtils.windowWidthPx - itemInfo.width) / 2);
      itemClipWidth = '100%';
      itemClipHeight = this.getUIContext().px2vp((itemInfo.height) / itemScale);
      itemTranslateY = this.getUIContext().px2vp(itemInfo.top - (
        (this.getUIContext().vp2px(itemClipHeight) - this.getUIContext().vp2px(itemClipHeight) * itemScale) / 2
      ));
    } else {
      itemTranslateY = this.getUIContext().px2vp(itemInfo.top - (WindowUtils.windowHeightPx - itemInfo.height) / 2);
      itemClipHeight = '100%';
      itemClipWidth = this.getUIContext().px2vp((itemInfo.width) / itemScale);
      itemTranslateX = this.getUIContext().px2vp(itemInfo.left - (WindowUtils.windowWidthPx / 2 - itemInfo.width / 2));
    }


    return {
      scale: itemScale,
      translateX: itemTranslateX ,
      translateY: itemTranslateY,
      clipWidth: itemClipWidth,
      clipHeight: itemClipHeight,
    }
  }


  // 照片页
  build() {
    Column() {
      Text('photo')
        .textAlign(TextAlign.Start)
        .width('100%')
        .fontSize(30)
        .padding(20)
      Image($r('app.media.startIcon'))
        .opacity(this.opacityDegree)
        .width('90%')
        .id('origin')// 挂载半模态页
        .enabled(this.isEnabled)
        .onClick(() => {
          // 获取原始图像的位置信息，将模态页上图片移动缩放至该位置
          this.originInfo = this.calculateData('origin');
          this.scaleValue = this.originInfo.scale;
          this.translateX = this.originInfo.translateX;
          this.translateY = this.originInfo.translateY;
          this.clipWidth = this.originInfo.clipWidth;
          this.clipHeight = this.originInfo.clipHeight;
          this.radius = 0;
          this.opacityDegree = 0;
          // 启动半模态页和模态页
          this.isShowSheet = true;
          this.isShowOverlay = true;
          // 设置原图为不可交互抗打断
          this.isEnabled = false;
        })
      Button('bindSheet page style: ' + this.preferTypeArrStr[this.preferTypeIndex])
        .fontSize(20)
        .margin({ top: 10 })
        .onClick(() => {
          this.preferTypeIndex = ++this.preferTypeIndex % this.preferTypeArr.length;
        })
    }
    .width('100%')
    .height('100%')
    .padding({ top: 20 })
    .alignItems(HorizontalAlign.Center)
    .bindSheet(this.isShowSheet, this.mySheet(), {
      // Embedded模式使得其他页面可以高于半模态页
      mode: SheetMode.EMBEDDED,
      height: this.bindSheetHeight,
      preferType: this.preferTypeArr[this.preferTypeIndex],
      onDisappear: () => {
        // 保证半模态消失时状态正确
        this.isShowImage = false;
        this.isShowSheet = false;
        // 设置一镜到底动画又进入可触发状态
        this.isAnimating = false;
        // 原图重新变为可交互状态
        this.isEnabled = true;
      }
    }) // 挂载模态页作为一镜到底动画的实现页
    .bindContentCover(this.isShowOverlay, this.overlayNode(), {
      // 模态页面设置为无转场
      transition: TransitionEffect.IDENTITY,
    })
  }


  // 半模态页面
  @Builder
  mySheet() {
    Column({space: 20}) {
      Text('bindSheet page')
        .fontSize(30)
      Row({space: 40}) {
        Column({space: 20}) {
          ForEach([1, 2, 3, 4], () => {
            Stack()
              .backgroundColor(Color.Pink)
              .borderRadius(20)
              .width(60)
              .height(60)
          })
        }
        Column() {
          if (this.isShowImage) {
            // 半模态页面的自定义图片节点
            ImageNode()
          } else {
            // 抓取布局和占位用，实际不显示
            Image($r('app.media.startIcon'))
              .visibility(Visibility.Hidden)
          }
        }
        .height(300)
        .width(200)
        .borderRadius(20)
        .clip(true)
        .id('target')
      }
      .alignItems(VerticalAlign.Top)
    }
    .alignItems(HorizontalAlign.Start)
    .height('100%')
    .width('100%')
    .margin(40)
  }


  @Builder
  overlayNode() {
    // Stack需要设置alignContent为TopStart，否则在高度变化过程中，截图和内容都会随高度重新布局位置
    Stack({ alignContent: Alignment.TopStart }) {
      ImageNode()
    }
    .scale({ x: this.scaleValue, y: this.scaleValue, centerX: undefined, centerY: undefined})
    .translate({ x: this.translateX, y: this.translateY })
    .width(this.clipWidth)
    .height(this.clipHeight)
    .borderRadius(this.radius)
    .clip(true)
  }
}


@Component
struct ImageNode {
  @State myNodeController: MyNodeController | undefined = new MyNodeController(false);


  aboutToAppear(): void {
    // 获取自定义节点
    let node = getMyNode();
    if (node == undefined) {
      // 新建自定义节点
      createMyNode(this.getUIContext());
    }
    this.myNodeController = getMyNode();
  }


  aboutToDisappear(): void {
    if (this.myNodeController != undefined) {
      // 节点下树
      this.myNodeController.onRemove();
    }
  }
  build() {
    NodeContainer(this.myNodeController)
  }
}