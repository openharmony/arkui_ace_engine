import curves from '@ohos.curves'

@Entry
@Component
struct GridItemExample {
  @State numbers: number[] = []
  @State dragItem: number = -1
  @State scaleItem: number = -1
  @State item: number = -1
  private dragRefOffsetx: number = 0
  private dragRefOffsety: number = 0
  @State offsetX: number = 0
  @State offsetY: number = 0
  private FIX_VP_X: number = 108
  private FIX_VP_Y: number = 120

  aboutToAppear() {
    for (let i = 1; i <= 11; i++) {
      this.numbers.push(i)
    }
  }

  itemMove(index: number, newIndex: number): void {
    console.info('index:' + index + ' newIndex:' + newIndex)
    if (!this.isDraggable(newIndex)) {
      return
    }
    let tmp = this.numbers.splice(index, 1)
    this.numbers.splice(newIndex, 0, tmp[0])
  }

  //向下滑
  down(index: number): void {
    // 指定固定GridItem不响应事件
    if (!this.isDraggable(index + 3)) {
      return
    }
    this.offsetY -= this.FIX_VP_Y
    this.dragRefOffsety += this.FIX_VP_Y
    this.itemMove(index, index + 3)
  }

  //向下滑(右下角为空)
  down2(index: number): void {
    if (!this.isDraggable(index + 3)) {
      return
    }
    this.offsetY -= this.FIX_VP_Y
    this.dragRefOffsety += this.FIX_VP_Y
    this.itemMove(index, index + 3)
  }

  //向上滑
  up(index: number): void {
    if (!this.isDraggable(index - 3)) {
      return
    }
    this.offsetY += this.FIX_VP_Y
    this.dragRefOffsety -= this.FIX_VP_Y
    this.itemMove(index, index - 3)
  }

  //向左滑
  left(index: number): void {
    if (!this.isDraggable(index - 1)) {
      return
    }
    this.offsetX += this.FIX_VP_X
    this.dragRefOffsetx -= this.FIX_VP_X
    this.itemMove(index, index - 1)
  }

  //向右滑
  right(index: number): void {
    if (!this.isDraggable(index + 1)) {
      return
    }
    this.offsetX -= this.FIX_VP_X
    this.dragRefOffsetx += this.FIX_VP_X
    this.itemMove(index, index + 1)
  }

  //向右下滑
  lowerRight(index: number): void {
    if (!this.isDraggable(index + 4)) {
      return
    }
    this.offsetX -= this.FIX_VP_X
    this.dragRefOffsetx += this.FIX_VP_X
    this.offsetY -= this.FIX_VP_Y
    this.dragRefOffsety += this.FIX_VP_Y
    this.itemMove(index, index + 4)
  }

  //向右上滑
  upperRight(index: number): void {
    if (!this.isDraggable(index - 2)) {
      return
    }
    this.offsetX -= this.FIX_VP_X
    this.dragRefOffsetx += this.FIX_VP_X
    this.offsetY += this.FIX_VP_Y
    this.dragRefOffsety -= this.FIX_VP_Y
    this.itemMove(index, index - 2)
  }

  //向左下滑
  lowerLeft(index: number): void {
    if (!this.isDraggable(index + 2)) {
      return
    }
    this.offsetX += this.FIX_VP_X
    this.dragRefOffsetx -= this.FIX_VP_X
    this.offsetY -= this.FIX_VP_Y
    this.dragRefOffsety += this.FIX_VP_Y
    this.itemMove(index, index + 2)
  }

  //向左上滑
  upperLeft(index: number): void {
    if (!this.isDraggable(index - 4)) {
      return
    }
    this.offsetX += this.FIX_VP_X
    this.dragRefOffsetx -= this.FIX_VP_X
    this.offsetY += this.FIX_VP_Y
    this.dragRefOffsety -= this.FIX_VP_Y
    this.itemMove(index, index - 4)
  }

  isDraggable(index: number): boolean {
    console.info('index:' + index)
    return index > 1
  }

  build() {
    Column() {
      Grid() {
        ForEach(this.numbers, (item: number) => {
          GridItem() {
            Text(item + '')
              .fontSize(16)
              .width('100%')
              .textAlign(TextAlign.Center)
              .height(100)
              .borderRadius(10)
              .backgroundColor(0xFFFFFF)
              .shadow(this.scaleItem == item ? {
                radius: 70,
                color: '#15000000',
                offsetX: 0,
                offsetY: 0
              } :
                {
                  radius: 0,
                  color: '#15000000',
                  offsetX: 0,
                  offsetY: 0
                })
              .animation({ curve: Curve.Sharp, duration: 300 })
          }
          // 指定固定GridItem不响应事件
          .hitTestBehavior(this.isDraggable(this.numbers.indexOf(item)) ? HitTestMode.Default : HitTestMode.None)
          .scale({ x: this.scaleItem == item ? 1.05 : 1, y: this.scaleItem == item ? 1.05 : 1 })
          .zIndex(this.dragItem == item ? 1 : 0)
          .translate(this.dragItem == item ? { x: this.offsetX, y: this.offsetY } : { x: 0, y: 0 })
          .padding(10)
          .gesture(
            // 以下组合手势为顺序识别，当长按手势事件未正常触发时则不会触发拖动手势事件
            GestureGroup(GestureMode.Sequence,
              LongPressGesture({ repeat: true })
                .onAction((event?: GestureEvent) => {
                  animateTo({ curve: Curve.Friction, duration: 300 }, () => {
                    this.scaleItem = item
                  })
                })
                .onActionEnd(() => {
                  animateTo({ curve: Curve.Friction, duration: 300 }, () => {
                    this.scaleItem = -1
                  })
                }),
              PanGesture({ fingers: 1, direction: null, distance: 0 })
                .onActionStart(() => {
                  this.dragItem = item
                  this.dragRefOffsetx = 0
                  this.dragRefOffsety = 0
                })
                .onActionUpdate((event: GestureEvent) => {
                  this.offsetY = event.offsetY - this.dragRefOffsety
                  this.offsetX = event.offsetX - this.dragRefOffsetx
                  animateTo({ curve: curves.interpolatingSpring(0, 1, 400, 38) }, () => {
                    let index = this.numbers.indexOf(this.dragItem)
                    if (this.offsetY >= this.FIX_VP_Y / 2 && (this.offsetX <= 44 && this.offsetX >= -44) &&
                      ![8, 9, 10].includes(index)) {
                      //向下滑
                      this.down(index)
                    } else if (this.offsetY <= -this.FIX_VP_Y / 2 && (this.offsetX <= 44 && this.offsetX >= -44) &&
                      ![0, 1, 2].includes(index)) {
                      //向上滑
                      this.up(index)
                    } else if (this.offsetX >= this.FIX_VP_X / 2 && (this.offsetY <= 50 && this.offsetY >= -50) &&
                      ![2, 5, 8, 10].includes(index)) {
                      //向右滑
                      this.right(index)
                    } else if (this.offsetX <= -this.FIX_VP_X / 2 && (this.offsetY <= 50 && this.offsetY >= -50) &&
                      ![0, 3, 6, 9].includes(index)) {
                      //向左滑
                      this.left(index)
                    } else if (this.offsetX >= this.FIX_VP_X / 2 && this.offsetY >= this.FIX_VP_Y / 2 &&
                      ![2, 5, 7, 8, 9, 10].includes(index)) {
                      //向右下滑
                      this.lowerRight(index)
                    } else if (this.offsetX >= this.FIX_VP_X / 2 && this.offsetY <= -this.FIX_VP_Y / 2 &&
                      ![0, 1, 2, 5, 8].includes(index)) {
                      //向右上滑
                      this.upperRight(index)
                    } else if (this.offsetX <= -this.FIX_VP_X / 2 && this.offsetY >= this.FIX_VP_Y / 2 &&
                      ![0, 3, 6, 9, 10].includes(index)) {
                      //向左下滑
                      this.lowerLeft(index)
                    } else if (this.offsetX <= -this.FIX_VP_X / 2 && this.offsetY <= -this.FIX_VP_Y / 2 &&
                      ![0, 1, 2, 3, 6, 9].includes(index)) {
                      //向左上滑
                      this.upperLeft(index)
                    } else if (this.offsetX >= this.FIX_VP_X / 2 && this.offsetY >= this.FIX_VP_Y / 2 &&
                    [7].includes(index)) {
                      //向右下滑(右下角为空)
                      this.down2(index)
                    }
                  })
                })
                .onActionEnd(() => {
                  animateTo({ curve: curves.interpolatingSpring(0, 1, 400, 38) }, () => {
                    this.dragItem = -1
                  })
                  animateTo({
                    curve: curves.interpolatingSpring(14, 1, 170, 17), delay: 150
                  }, () => {
                    this.scaleItem = -1
                  })
                })
            )
              .onCancel(() => {
                animateTo({ curve: curves.interpolatingSpring(0, 1, 400, 38) }, () => {
                  this.dragItem = -1
                })
                animateTo({
                  curve: curves.interpolatingSpring(14, 1, 170, 17)
                }, () => {
                  this.scaleItem = -1
                })
              })
          )
        }, (item: number) => item.toString())
      }
      .width('90%')
      .editMode(true)
      .scrollBar(BarState.Off)
      .columnsTemplate('1fr 1fr 1fr')
    }.width('100%').height('100%').backgroundColor('#0D182431').padding({ top: 5 })
  }
}