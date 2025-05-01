let COLUMN_NUMBER = 5;
let COLUMNS_GAP = 20;
let ROWS_GAP = 20;

@Entry
@Component
struct SwiperHeight {
  build() {
    Column() {
      // 修改成搜索框
      Text('头部区域')
        .textAlign(TextAlign.Center)
        .backgroundColor(Color.Yellow)
        .width('100%')
        .height('40')
      GridDemo()
        .width('90%')
      Text('尾部区域')
        .textAlign(TextAlign.Center)
        .backgroundColor(Color.Green)
        .width('100%')
        .height('30%')
    }
  }
}

@Component
struct GridDemo {
  @State gridHeights: number[] = []
  @State swiperHeight: number = 0
  @State message: string = 'Hello World';
  @State tipList: string[] = ['数学', '语文', '英语', '生物']
  @State tipImageX: string = '0%'
  @State tipIndex: number = 0
  @State numberList: number[][] = [
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30]]
  private swiperController: SwiperController = new SwiperController()

  aboutToAppear(): void {
    this.getHeights()
  }

  getHeights() {
    for (let index = 0; index < this.numberList.length; index++) {
      let rowNumber = Math.ceil(this.numberList[index].length / COLUMN_NUMBER)
      let gridHeight = px2vp(122) * rowNumber + COLUMNS_GAP * (rowNumber - 1)
      this.gridHeights.push(gridHeight)
    }
    this.swiperHeight = this.gridHeights[0]
  }

  build() {
    Column() {
      Stack() {
        Image($r('app.media.background'))
          .objectFit(ImageFit.Contain)
          .width((100 / this.tipList.length) + '%')
          .offset({ x: this.tipImageX })
        Row() {
          ForEach(this.tipList, (item: string, index) => {
            ListItem() {
              Text(item)
                .backgroundImage(this.tipIndex == index ? $r('app.media.startIcon') : null, ImageRepeat.NoRepeat)
                .backgroundImageSize({ width: '100%', height: '100%' })
            }
          }, (item: string) => item)
        }
        .justifyContent(FlexAlign.SpaceAround)
        .height(20)
        .width('100%')
        .margin({ top: 5, bottom: 5 })
      }
      .alignContent(Alignment.Start)
      .height(30)
      .backgroundColor(Color.Pink)

      Column() {
        Swiper(this.swiperController) {
          ForEach(this.numberList, (item: number, index) => {
            Child({ numberList: this.numberList[index] })
          })
        }
        .effectMode(EdgeEffect.None)
        .indicator(false)
        .loop(false)
        .onContentDidScroll((selectedIndex: number, index: number, position: number, mainAxisLength: number) => {
          // 两个index直接的滚动位置改变父控件高度
          if (selectedIndex != index && Math.abs(selectedIndex - index) == 1) {
            let curHeight = this.gridHeights[selectedIndex]
            let targetHeight = this.gridHeights[index]
            this.swiperHeight = targetHeight +
              (selectedIndex < index ? (curHeight - targetHeight) : (targetHeight - curHeight)) * position
          }
          // $r('app.media.background')的位置和当前选中状态的下标切换
          if (selectedIndex == index) {
            let curIndex = -1 / this.tipList.length * position + selectedIndex / this.tipList.length
            this.tipImageX = (curIndex * 100).toFixed(2) + '%'
            this.tipIndex = Math.ceil(curIndex * this.tipList.length + 0.5) - 1
          }
        })
      }.height(this.swiperHeight)
    }
    .width('100%')
  }
}


@Component
struct Child {
  @Prop numberList: number[];

  build() {
    Grid() {
      ForEach(this.numberList, (item: number) => {
        GridItem() {
          Column() {
            Image($r('app.media.startIcon'))
              .width(20)
              .height(20)
            Text('菜单' + item)
              .fontSize(15)
          }
        }
      })
    }
    .columnsGap(COLUMNS_GAP)
    .rowsGap(ROWS_GAP)
    .scrollBar(BarState.Off)
    .columnsTemplate('1fr '.repeat(COLUMN_NUMBER))
    .animation({
      duration: 1000
    })
  }
}