import { ImgEntity } from './ImgEntity';
import { createRandomInteger } from './Utils';

@Component
export struct ProductCardWidget {
  @ObjectLink item: ImgEntity;
  index: number = 0;
  maxRatioSize: number = 1.5;
  minRatioSize: number = 1;
  @State componentRatio: number = 1.0;
  private timerId?: number;
  @State imageString: string = 'app.media.background';

  aboutToAppear() {
    this.imageString = 'app.media.startIcon';
    this.componentRatio = this.item.ratio ?? 1.0;
    if (this.item.ratio == 0) {
      let delayTime = createRandomInteger(1, 4);
      // setTimeout 延迟改变高度
      this.timerId = setTimeout(() => {
        this.componentRatio = 1 + createRandomInteger(0, 40) / 100;
        this.item.ratio = this.componentRatio;
      }, delayTime);
    }
  }

  aboutToDisappear() {
    if (this.timerId) {
      clearTimeout(this.timerId);
    }
  }

  build() {
    Column() {
      Column() {
        Text('图片').fontColor(Color.Black)
      }
      .width('100%')
      .height(100)
      //.aspectRatio(1 / this.componentRatio) //真机上测试时使用这个
      .alignItems(HorizontalAlign.Center)
      .justifyContent(FlexAlign.Center)
      .backgroundColor(this.item.color)
      .borderRadius({
        topLeft: 4,
        topRight: 4
      })

      Column() {
        Text(`第${this.index + 1}个`)
      }
      .width('100%')
      .height(50)
      .alignItems(HorizontalAlign.Center)
      .justifyContent(FlexAlign.Center)
      .backgroundColor(Color.Orange)
      .borderRadius({
        bottomLeft: 4,
        bottomRight: 4
      })
    }
    .width('100%')
    .height('auto')
  }
}
