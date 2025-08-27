// 使用Scroll+Row实现自适应子组件高度的横滑“Grid”

@Entry
@Component
struct ScrollToGrid {
  @State message: string = '改变item高度';
  @State itemHeight: number = 100;
  private imageArray1: number[] = [0, 1, 2, 3, 4, 5];
  private imageArray2: number[] = [0, 1, 2, 3, 4, 5];
  private textArray: string[] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11'];

  build() {
    List() {
      ListItem() {
        Text(this.message)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            if (this.itemHeight === 100) {
              this.itemHeight = 120;
            } else {
              this.itemHeight = 100;
            }
          })
      }
      .width('100%')

      ListItem() {
        Scroll() {
          Column({ space: 20 }) {
            Row({ space: 20 }) {
              ForEach(this.imageArray1, () => {
                Image($r('app.media.startIcon'))
                  .height(this.itemHeight)
              }, (item: number) => item.toString())
            }

            Row({ space: 20 }) {
              ForEach(this.imageArray2, () => {
                Image($r('app.media.startIcon')).height((this.itemHeight))
              })
            }
          }
        }
        .scrollable(ScrollDirection.Horizontal)
        .scrollBar(BarState.Off)
      }

      ForEach(this.textArray, (item: string) => {
        ListItem() {
          Text('ListItem:' + item).fontSize(50)
        }
      }, (item: string) => item)
    }
    .height('100%')
  }
}