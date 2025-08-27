/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// 使用手势实现任意组件的自由滚动

import animator, { AnimatorResult } from '@ohos.animator';

export enum OverScrollMode {
  DISABLE = 0,
  ENABLE = 1,
  ALWAYS_ENABLE = 2,
}

export enum BarState {
  Off = 0,
  On = 1,
  Auto = 2,
}

export enum BarDirection {
  Vertical = 0,
  Horizontal = 1,
  BOTH = 2,
}

@Component
export struct FreeScroll {
  @Builder  doNothingBuilder() {};
  @BuilderParam builder: () => void = this.doNothingBuilder;
  @Link @Watch('onContentSizeUpdate') contentSize:SizeResult
  prevContentSize:SizeResult = {width:100, height:100};
  @State xOffset:number = 0
  @State yOffset:number = 0
  @State xBarOffset:number = 0
  @State yBarOffset:number = 0
  @State height1:number = 0
  @State width1:number = 0
  private xBarPadding:number = 20
  private yBarPadding:number = 30
  private panXOffset:number = 0
  private panYOffset:number = 0
  private selfHeight: number = 0
  private selfWidth: number = 0
  private wLimit: number = 0
  private hLimit: number = 0
  private scrollXAnimator: AnimatorResult | undefined = undefined
  private scrollYAnimator: AnimatorResult | undefined = undefined
  @State isViable:boolean = true
  private xLimit: number = 0
  private yLimit: number = 0
  private overScrollX: boolean = false
  private overScrollY: boolean = false
  private timeoutPanID:number = 0
  private timeoutUpdateID:number = 0
  private timeoutScaleID:number = 0

  @State contentScale:number = 1.0
  private prevScale:number = 1.0
  private contentScaleStart:number = 1.0
  maxScale: number = 4
  minScale: number = 0.5
  maxOverScale: number = 0.6
  private pinchXOffset: number = 0
  private pinchYOffset: number = 0
  private scaleAnimator: AnimatorResult | undefined = undefined

  @Prop overScrollMode:OverScrollMode
  @Prop barState:BarState
  @Prop barDirection:BarDirection
  @Prop initAlign:Alignment
  private isInit:boolean = true;

  aboutToAppear() {
    this.prevContentSize.width = this.contentSize.width;
    this.prevContentSize.height = this.contentSize.height;
  }

  onContentSizeUpdate():void {
    this.xLimit = Math.max(0, (this.contentSize.width * this.contentScale - this.selfWidth) / 2);
    this.yLimit = Math.max(0, (this.contentSize.height * this.contentScale - this.selfHeight) / 2);
    this.xOffset = this.xOffset + (this.contentSize.width - this.prevContentSize.width) / 2
    this.xOffset = Math.max(-this.xLimit, Math.min(this.xLimit, this.xOffset))
    this.yOffset = this.yOffset + (this.contentSize.height - this.prevContentSize.height) / 2
    this.yOffset = Math.max(-this.yLimit, Math.min(this.yLimit, this.yOffset))
    this.width1 = Math.min(this.selfWidth / this.contentScale / this.contentSize.width * this.wLimit, this.wLimit);
    this.height1 = Math.min(this.selfHeight / this.contentScale / this.contentSize.height * this.hLimit, this.hLimit);
    this.xBarOffset = this.xLimit == 0 ? 0 : (this.width1 - this.wLimit) / 2 * this.xOffset / this.xLimit
    this.yBarOffset = this.yLimit == 0 ? 0 : (this.height1 - this.hLimit) / 2 * this.yOffset / this.yLimit
    this.prevContentSize = this.contentSize;
    if (this.barState == BarState.Auto) {
      clearTimeout(this.timeoutPanID);
      clearTimeout(this.timeoutScaleID);
      this.isViable = true
      this.timeoutUpdateID = setTimeout(() => {
        this.isViable = false
      }, 2000);
    }
  }

  createScrollAnimator(start:number, limit: number, velocity:number):AnimatorResult {
    if (-limit <= start && start <= limit) {
      let friction = 1.4
      let FRICTION_SCALE = -4.2
      let response = Math.abs(2 * Math.PI / (-4.2 * friction))
      let tmpStiffness = (2 * Math.PI / response);
      let stiffness = tmpStiffness * tmpStiffness;
      let damping = 4 * Math.PI / response;
      let end = start + velocity / (friction * -FRICTION_SCALE)
      let v = velocity / (end - start)
      return animator.create({
        duration: 2000,
        easing: 'interpolating-spring(' + v + ',1,' + stiffness + ',' + damping + ')',
        delay: 0,
        fill: 'forwards',
        direction: 'normal',
        iterations: 1,
        begin: start,
        end: end
      })
    } else {
      let end = start > limit ? limit : - limit
      let v = velocity / (end - start)
      return animator.create({
        duration: 2000,
        easing: 'interpolating-spring(' + v + ',1,228,30)',
        delay: 0,
        fill: 'forwards',
        direction: 'normal',
        iterations: 1,
        begin: start,
        end: end
      })
    }
  }

  createScaleAnimator(start:number, end:number):AnimatorResult {
    return animator.create({
      duration: 2000,
      easing: 'interpolating-spring(0,1,228,30)',
      delay: 0,
      fill: 'forwards',
      direction: 'normal',
      iterations: 1,
      begin: start,
      end: end
    })
  }

  UpdateOffsetForScale() {
    let cx = this.pinchXOffset - (this.selfWidth / 2);
    let dx = (this.xOffset - cx) * (this.contentScale - this.prevScale)
    this.xOffset = Math.max(-this.xLimit, Math.min(this.xLimit, this.xOffset + dx / this.contentScale))
    let cy = this.pinchYOffset - (this.selfHeight / 2);
    let dy = (this.yOffset - cy) * (this.contentScale - this.prevScale)
    this.yOffset = Math.max(-this.yLimit, Math.min(this.yLimit, this.yOffset + dy / this.contentScale))
    this.width1 = Math.min(this.selfWidth / this.contentScale / this.contentSize.width * this.wLimit, this.wLimit);
    this.height1 = Math.min(this.selfHeight / this.contentScale / this.contentSize.width * this.hLimit, this.hLimit);
    this.xBarOffset = this.xLimit == 0 ? 0 : (this.width1 - this.wLimit) / 2 * this.xOffset / this.xLimit
    this.yBarOffset = this.yLimit == 0 ? 0 : (this.height1 - this.hLimit) / 2 * this.yOffset / this.yLimit
  }

  build() {
    Stack() {
      Stack() {
        this.builder()
      }
      .height('100%')
      .width('100%')
      .translate({x:this.xOffset, y:this.yOffset})
      .scale({x:this.contentScale, y: this.contentScale})

      if (this.barState != BarState.Off &&
        (this.barDirection == BarDirection.Horizontal || this.barDirection == BarDirection.BOTH)) {
        Stack(){}
        .borderRadius(50)
        .backgroundColor(Color.Gray)
        .width(this.width1)
        .height(8)
        .translate({x:this.xBarOffset, y:this.selfHeight/2 - this.xBarPadding})
        .visibility(this.isViable ? Visibility.Visible : Visibility.None)
      }
      if (this.barState != BarState.Off &&
        (this.barDirection == BarDirection.Vertical || this.barDirection == BarDirection.BOTH)) {
        Stack(){}
        .borderRadius(50)
        .backgroundColor(Color.Gray)
        .width(8)
        .height(this.height1)
        .translate({x:this.selfWidth/2 - this.yBarPadding, y:this.yBarOffset})
        .visibility(this.isViable ? Visibility.Visible : Visibility.None)
      }
    }
    .clip(true)
    .height('100%')
    .width('100%')
    .backgroundColor(Color.Blue)
    .onTouch((event: TouchEvent)=>{
      if (event.type == TouchType.Down) {
        this.scrollXAnimator?.pause()
        this.scrollYAnimator?.pause()
        clearTimeout(this.timeoutPanID);
        clearTimeout(this.timeoutUpdateID);
        clearTimeout(this.timeoutScaleID);
      }
    })
    .gesture(GestureGroup(GestureMode.Parallel,
      PanGesture()
        .onActionStart((event?: GestureEvent) => {
          this.panXOffset = 0
          this.panYOffset = 0
          this.scrollXAnimator?.pause()
          this.scrollYAnimator?.pause()
          clearTimeout(this.timeoutPanID);
          clearTimeout(this.timeoutUpdateID);
          clearTimeout(this.timeoutScaleID);
        })
        .onActionUpdate((event?: GestureEvent) => {
          if (event) {
            let dx = event.offsetX - this.panXOffset;
            let canOverScrollX = ((this.contentSize.width * this.contentScale > this.selfWidth) &&
              this.overScrollMode == OverScrollMode.ENABLE) || this.overScrollMode == OverScrollMode.ALWAYS_ENABLE;
            if (this.xOffset > this.xLimit) {
              let friction = (1 - (this.xOffset - this.xLimit) / this.selfWidth)
              dx *= friction * friction
            } else if (this.xOffset < -this.xLimit) {
              let friction = (1 - (-this.xOffset - this.xLimit) / this.selfWidth)
              dx *= friction * friction
            }
            this.xOffset += dx;
            if (!canOverScrollX) {
              this.xOffset = Math.max(Math.min(this.xOffset, this.xLimit), -this.xLimit)
            }
            this.overScrollX = !(-this.xLimit <= this.xOffset && this.xOffset <= this.xLimit);

            let dy = event.offsetY - this.panYOffset
            let canOverScrollY = ((this.contentSize.height * this.contentScale > this.selfHeight) &&
              this.overScrollMode == OverScrollMode.ENABLE) || this.overScrollMode == OverScrollMode.ALWAYS_ENABLE;
            if (this.yOffset > this.yLimit) {
              let friction = (1 - (this.yOffset - this.yLimit) / this.selfHeight)
              dy *= friction * friction
            } else if (this.yOffset < -this.yLimit) {
              let friction = (1 - (-this.yOffset - this.yLimit) / this.selfHeight)
              dy *= friction * friction
            }
            this.yOffset += dy;
            if (!canOverScrollY) {
              this.yOffset = Math.max(Math.min(this.yOffset, this.yLimit), -this.yLimit)
            }
            this.overScrollY = !(-this.yLimit <= this.yOffset && this.yOffset <= this.yLimit);

            this.panXOffset = event.offsetX
            this.panYOffset = event.offsetY
            this.pinchXOffset += dx;
            this.pinchYOffset += dy;
            this.xBarOffset = this.xLimit == 0 ? 0 : (this.width1 - this.wLimit) / 2 * this.xOffset / this.xLimit
            this.yBarOffset = this.yLimit == 0 ? 0 : (this.height1 - this.hLimit) / 2 * this.yOffset / this.yLimit

            if (this.barState == BarState.Auto) {
              this.isViable = true
            }
          }
        })
        .onActionEnd((event: GestureEvent) => {
          if (this.barState == BarState.Auto) {
            this.timeoutPanID = setTimeout(() => {
              this.isViable = false
            }, 2000);
          }
          if ((this.overScrollX || Math.abs(event.velocityX) > 10) && Math.abs(event.velocityX) != Infinity) {
            this.scrollXAnimator = this.createScrollAnimator(this.xOffset, this.xLimit, event.velocityX)
            this.scrollXAnimator.onframe = (value: number) => {
              if (this.overScrollX) {
                this.xOffset = value
              } else {
                this.xOffset = Math.max(-this.xLimit, Math.min(this.xLimit, value))
              }
              this.xBarOffset = this.xLimit == 0 ? 0 : (this.width1 - this.wLimit) / 2 * this.xOffset / this.xLimit
              this.xBarOffset = Math.max((this.width1 - this.wLimit) / 2,
                Math.min(this.xBarOffset, (this.wLimit - this.width1) / 2))
            }
            this.scrollXAnimator.play()
          }
          if ((this.overScrollY || Math.abs(event.velocityY) > 10) && Math.abs(event.velocityY) != Infinity) {
            this.scrollYAnimator = this.createScrollAnimator(this.yOffset, this.yLimit, event.velocityY)
            this.scrollYAnimator.onframe = (value: number) => {
              if (this.overScrollY) {
                this.yOffset = value
              } else {
                this.yOffset = Math.max(-this.yLimit, Math.min(this.yLimit, value))
              }
              this.yBarOffset = this.yLimit == 0 ? 0 : (this.height1 - this.hLimit) / 2 * this.yOffset / this.yLimit
              this.yBarOffset = Math.max((this.height1 - this.hLimit) / 2,
                Math.min(this.yBarOffset, (this.hLimit - this.height1) / 2))
            }
            this.scrollYAnimator.play()
          }
        }),
      PinchGesture()
        .onActionStart((event: GestureEvent)=>{
          this.contentScaleStart = this.contentScale
          this.pinchXOffset = event.pinchCenterX
          this.pinchYOffset = event.pinchCenterY
          this.prevScale = this.contentScale
          this.scaleAnimator?.finish()
          clearTimeout(this.timeoutPanID);
          clearTimeout(this.timeoutUpdateID);
          clearTimeout(this.timeoutScaleID);
        })
        .onActionUpdate((event: GestureEvent)=>{
          let scale = this.contentScaleStart * event.scale
          this.xLimit = Math.max(0, (this.contentSize.width * this.contentScale - this.selfWidth) / 2);
          this.yLimit = Math.max(0, (this.contentSize.height * this.contentScale - this.selfHeight) / 2);
          if (scale > this.maxScale) {
            let friction = -this.maxOverScale * this.maxScale / scale + this.maxOverScale
            this.contentScale = this.maxScale * (1 + friction)
          } else if (scale < this.minScale) {
            let friction = -this.maxOverScale * scale / this.minScale + this.maxOverScale
            this.contentScale = this.minScale * (1 - friction)
          } else {
            this.contentScale = scale
          }

          this.UpdateOffsetForScale();
          this.prevScale = this.contentScale
          this.width1 =
            Math.min(this.selfWidth / this.contentScale / this.contentSize.width * this.wLimit, this.wLimit);
          this.height1 =
            Math.min(this.selfHeight / this.contentScale / this.contentSize.width * this.hLimit, this.hLimit);
          this.xBarOffset = this.xLimit == 0 ? 0 : (this.width1 - this.wLimit) / 2 * this.xOffset / this.xLimit
          this.yBarOffset = this.yLimit == 0 ? 0 : (this.height1 - this.hLimit) / 2 * this.yOffset / this.yLimit

          if (this.barState == BarState.Auto) {
            this.isViable = true;
          }
        })
        .onActionEnd(()=>{
          if (this.barState == BarState.Auto) {
            this.timeoutScaleID = setTimeout(() => {
              this.isViable = false
            }, 2000);
          }
          if (this.contentScale > this.maxScale) {
            this.scaleAnimator = this.createScaleAnimator(this.contentScale, this.maxScale)
          } else if (this.contentScale < this.minScale) {
            this.scaleAnimator = this.createScaleAnimator(this.contentScale, this.minScale)
          } else {
            return;
          }
          this.scaleAnimator.onframe = (value:number)=>{
            this.contentScale = value;
            this.xLimit = Math.max(0, (this.contentSize.width * this.contentScale - this.selfWidth) / 2);
            this.yLimit = Math.max(0, (this.contentSize.height * this.contentScale - this.selfHeight) / 2);
            this.UpdateOffsetForScale();
            this.prevScale = this.contentScale;
            this.xBarOffset = Math.max((this.width1 - this.wLimit) / 2,
                Math.min(this.xBarOffset, (this.wLimit - this.width1) / 2))
            this.yBarOffset = Math.max((this.height1 - this.hLimit) / 2,
                Math.min(this.yBarOffset, (this.hLimit - this.height1) / 2))
          }
          this.scaleAnimator.play();
        })
    )
    )
    .onAreaChange((oldValue: Area, newValue: Area) => {
      this.selfHeight = newValue.height as number
      this.selfWidth = newValue.width as number
      this.wLimit = this.selfWidth - this.xBarPadding * 2
      this.hLimit = this.selfHeight - this.yBarPadding * 2
      this.xLimit = Math.max(0, (this.contentSize.width * this.contentScale - this.selfWidth) / 2);
      this.yLimit = Math.max(0, (this.contentSize.height * this.contentScale - this.selfHeight) / 2);
      this.width1 = Math.min(this.selfWidth / this.contentScale / this.contentSize.width * this.wLimit, this.wLimit);
      this.height1 = Math.min(this.selfHeight / this.contentScale / this.contentSize.height * this.hLimit, this.hLimit);
      if (this.isInit) {
        switch (this.initAlign) {
          case Alignment.TopStart:
            this.xOffset = this.xLimit
            this.yOffset = this.yLimit
            break;
          case Alignment.Top:
            this.yOffset = this.yLimit
            break;
          case Alignment.TopEnd:
            this.xOffset = -this.xLimit
            this.yOffset = this.yLimit
            break;
          case Alignment.Start:
            this.xOffset = this.xLimit;
            break;
          case Alignment.Center:
            break;
          case Alignment.End:
            this.xOffset = -this.xLimit;
            break;
          case Alignment.BottomStart:
            this.xOffset = this.xLimit;
            this.yOffset = -this.yLimit;
            break;
          case Alignment.Bottom:
            this.yOffset = -this.yLimit
            break;
          case Alignment.BottomEnd:
            this.xOffset = -this.xLimit;
            this.yOffset = -this.yLimit
            break;
        }
        this.isInit = false;
      }
      this.xBarOffset = this.xLimit == 0 ? 0 : (this.width1 - this.wLimit) / 2 * this.xOffset / this.xLimit
      this.yBarOffset = this.yLimit == 0 ? 0 : (this.height1 - this.hLimit) / 2 * this.yOffset / this.yLimit
      if (this.barState == BarState.Auto) {
        setTimeout(() => {
          this.isViable = false;
        }, 2000);
      }
    })
  }
}

@Entry
@Component
struct Index {
  @State contentSize: SizeResult = {width:900, height:900}

  build() {
    Stack() {
      FreeScroll({ contentSize: this.contentSize,
        overScrollMode: OverScrollMode.ENABLE,
        initAlign:Alignment.TopStart}) {
        Image($r('app.media.startIcon'))
          .height(900)
          .width(900)
      }
    }
  }
}