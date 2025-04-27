/**
 * 0-初始化页面
 * 1、打开demo页面。
 * 2、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 
 * 说明：
 * 1、Swiper1和导航点1绑定，受controller1控制。
 * 2、Swiper2和导航点2绑定，受controller2控制。
 */

/**
 * 1-场景1：
 * Indicator1和Swiper1绑定，受controller2控制。
 * Indicator2和Swiper2绑定，受controller1控制。
 * 
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景1按钮。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 
 * 预期结果：
 * Indicator1和Swiper1绑定，受controller2控制。
 * Indicator2和Swiper2绑定，受controller1控制。
 */

/**
 * 2-场景2：
 * Indicator2不变，切换Indicator1。
 * 
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景2-1按钮。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 2、点击场景2-2按钮。
 * 
 * 场景2-1：
 * 1、Indicator1受controller2控制。
 * 2、Indicator2不再受controller2控制。
 * 
 * 场景2-2：
 * 1、Indicator1受controller1控制。
 * 2、Indicator2不再受controller2控制。
 */

/**
 * 3-场景3：
 * Swiper2不变，切换Swiper1。
 * 
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景3-1按钮。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 2、点击场景3-2按钮。
 * 
 * 场景3-1：
 * 1、Swiper1受controller2控制,Swiper1和Indicator1解绑。
 * 2、Indicator2不再受controller2控制。
 * 
 * 场景3-2：
 * 1、Swiper1受controller1控制，Swiper1和Indicator1重新绑定。
 * 2、Swiper2和Indicator2解绑；Indicator2不再受controller2控制。
 */

/**
 * 4-场景4：
 * indicator不变，切换swiper1和swiper2。
 * 
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景4按钮。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 
 * 预期结果：
 * swiper1和indicator2绑定，受controller2控制。
 * swiper2和indicator1绑定，受controller1控制。
 */

/**
 * 5-场景5：
 * swiper不变，切换indicator1和indicator2。
 * 
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景5按钮。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 
 * 预期效果同场景4。
 */

/**
 * 6-场景6：
 * 数字导航点切换
 * 
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景6-1按钮 切换导航点样式。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 2、点击场景6-2按钮 切换导航点样式。
 * 
 * 说明：
 * 1、场景6-1，导航点1更新。
 * 2、场景6-2，导航点2更新。
 * 原则：相同controller控制不同导航点时，以最后一次更新的为准。
 */

/**
 * 7-场景7：
 * "内置" 和 "绑定"，进行切换
 * 
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景7按钮 切换导航点样式。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 
 * 预期结果：
 * 导航点类型正确切换，丢失绑定的时候单独导航点状态刷新。
 */


class MyDataSource1 implements IDataSource {
  private list: number[] = []

  constructor(list: number[]) {
    this.list = list
  }

  totalCount(): number {
    return this.list.length
  }

  getData(index: number): number {
    return this.list[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
  }

  unregisterDataChangeListener() {
  }
}

@Entry
@Component
struct Index111 {

  UpdateIndicaotr(): IndicatorComponentController | DotIndicator | DigitIndicator | boolean {
    switch (this.swiper2_controller) {
      case 0:
        return new DotIndicator();
      case 1:
        return this.indicatorController1;
      case 2:
        return this.indicatorController2;
      case 3:
        return true;
      case 4:
        return false;
      case 5:
        return new DigitIndicator();
      default:
        return false;
    }
  }
  @State count: number = 5;
  private indicatorController1: IndicatorComponentController = new IndicatorComponentController()
  private indicatorController2: IndicatorComponentController = new IndicatorComponentController()
  private data: MyDataSource1 = new MyDataSource1([])
  @State isDigIndicator1: boolean = false;
  @State isDigIndicator2: boolean = false;
  private swiperController1: SwiperController = new SwiperController()
  private swiperController2: SwiperController = new SwiperController()
  @State swiper1_controller: number = 1
  @State swiper2_controller: number = 2
  @State indicator1_controller: number = 1
  @State indicator2_controller: number = 2

  aboutToAppear(): void {
    let list: number[] = []
    for (let i = 0; i < 9; i++) {
      list.push(i);
    }
    this.data = new MyDataSource1(list)
  }

  build() {
    Column() {
      Row() {
        Button('showNext1')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicatorController1.showNext()

          })
        Button('showPrevious1')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicatorController1.showPrevious()
          })
        Button('showNext2')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicatorController2.showNext()

          })
        Button('showPrevious2')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicatorController2.showPrevious()
          })
      }

      Swiper(this.swiperController1) {
        LazyForEach(this.data, (item: string) => {
          Text(item.toString())
            .width('90%')
            .height(160)
            .backgroundColor(0xAFEEEE)
            .textAlign(TextAlign.Center)
            .fontSize(30)
        }, (item: string) => item)
      }
      .margin(10)
      .loop(false)
      .indicator(this.swiper1_controller == 1 ? this.indicatorController1 : this.indicatorController2)
      .vertical(false)

      Swiper(this.swiperController2) {
        LazyForEach(this.data, (item: string) => {
          Text(item.toString())
            .width('90%')
            .height(160)
            .backgroundColor(0xAFEEEE)
            .textAlign(TextAlign.Center)
            .fontSize(30)
        }, (item: string) => item)
      }
      .margin(10)
      .loop(false)
      .indicator(this.UpdateIndicaotr())
      .vertical(false)

      IndicatorComponent(this.indicator1_controller == 1 ? this.indicatorController1 : this.indicatorController2)
        .style(this.isDigIndicator1 ? new DigitIndicator() :
          new DotIndicator()
        )
        .loop(false)
        .count(this.count)
        .vertical(false)

      IndicatorComponent(this.indicator2_controller == 1 ? this.indicatorController1 : this.indicatorController2)
        .style(this.isDigIndicator2 ? new DigitIndicator() :
          new DotIndicator()
        )
        .loop(false)
        .count(this.count)
        .vertical(false)
      Row() {
        Button('场景1')
          .margin({ top: 5 })
          .onClick(() => {
            this.swiper1_controller = 2;
            this.swiper2_controller = 1;
            this.indicator1_controller = 2;
            this.indicator2_controller = 1;
          })
        Button('场景2-1')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicator1_controller = 2;
          })
        Button('场景2-2')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicator1_controller = 1;
          })
        Button('场景3-1')
          .margin({ top: 5 })
          .onClick(() => {
            this.swiper1_controller = 2;
          })
        Button('场景3-2')
          .margin({ top: 5 })
          .onClick(() => {
            this.swiper1_controller = 1;
          })
      }

      Row() {
        Button('场景4')
          .margin({ top: 5 })
          .onClick(() => {
            this.swiper1_controller = 2;
            this.swiper2_controller = 1;
          })
        Button('场景5')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicator1_controller = 2;
            this.indicator2_controller = 1;
          })
        Button('场景6 - 1')
          .margin({ top: 5 })
          .onClick(() => {
            this.isDigIndicator1 = !this.isDigIndicator1;
          })
        Button('场景6 - 2')
          .margin({ top: 5 })
          .onClick(() => {
            this.isDigIndicator2 = !this.isDigIndicator2;
          })
      }
      Row(){
        Button('场景7 swiper2_controller = ' + this.swiper2_controller)
          .margin({ top: 5 })
          .onClick(() => {
            this.swiper2_controller = (this.swiper2_controller + 1) % 6;
          })
      }
    }
    .width('100%')
  }
}