@Entry
@Component
struct labelInfoTest {
  @State textFontSize: number = 15
  @State textChange1: string = '字体大小15（点击展示菜单）'
  @State textFontWeight: number = 400
  @State textChange2: string = '字体自重400（点击展示菜单）'
  @State textFontColor: string = 'red'
  @State textChange3: string = '字体颜色-红（点击展示菜单）'
  @State rotateAngle: number = 0
  private flag: boolean = true
  @Builder
  MyMenu1(){
    Menu() {
      MenuItem({ labelInfo: this.textChange1 }).labelFont({ size: this.textFontSize })
    }.width('100%')
  }
  @Builder
  MyMenu2(){
    Menu() {
      MenuItem({ labelInfo: this.textChange2 }).labelFont({ weight: this.textFontWeight })
    }.width('100%')
  }
  @Builder
  MyMenu3(){
    Menu() {
      MenuItem({ labelInfo: this.textChange3 }).labelFontColor(this.textFontColor)
    }.width('100%')
  }

  build() {

    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceAround }) {
      Column() {
        Button('changeSize')
          .key('labelInfoChangeSize')
          .margin(30)
          .onClick(() => {
            if (this.flag) {
              animateTo({
                duration: 2000,
                curve: Curve.EaseOut,
                iterations: 1,
                playMode: PlayMode.Normal,
                onFinish: () => {
                  console.info('play end')
                }
              }, () => {
                this.textFontSize = 30
                this.textChange1 = '字体大小30（点击展示菜单）'
              })
            }
            this.flag = !this.flag
          })
        Text(this.textChange1)
          .fontSize(this.textFontSize)
          .width('100%')
          .height('50%')
          .textAlign(TextAlign.Center)
      }.backgroundColor('#F0F0F0').height('25%').bindMenu(this.MyMenu1)

      Column() {
        Button('changeWeight')
          .key('labelInfoChangeWeight')
          .margin(30)
          .onClick(() => {
            if (this.flag) {
              animateTo({
                duration: 2000,
                curve: Curve.EaseOut,
                iterations: 1,
                playMode: PlayMode.Normal,
                onFinish: () => {
                  console.info('play end')
                }
              }, () => {
                this.textFontWeight = 900
                this.textChange2 = '字体自重900（点击展示菜单）'
              })
            }
            this.flag = !this.flag
          })

        Text(this.textChange2)
          .fontSize(30)
          .fontWeight(this.textFontWeight)
          .width('100%')
          .height('50%')
          .textAlign(TextAlign.Center)
      }.backgroundColor('#F0F0F0').height('25%').bindMenu(this.MyMenu2)

      Column() {
        Button('changeColor')
          .key('labelInfoChangeColor')
          .margin(30)
          .onClick(() => {
            if (this.flag) {
              animateTo({
                duration: 5000,
                curve: Curve.EaseOut,
                iterations: 1,
                playMode: PlayMode.Normal,
                onFinish: () => {
                  console.info('play end')
                }
              }, () => {
                this.textFontColor = 'green'
                this.textChange3 = '字体颜色-绿（点击展示菜单）'
              })
            }
            this.flag = !this.flag
          })

        Text(this.textChange3)
          .fontSize(30)
          .fontColor(this.textFontColor)
          .width('100%')
          .height('50%')
          .textAlign(TextAlign.Center)
      }.backgroundColor('#F0F0F0').height('25%').bindMenu(this.MyMenu3)
    }
    .width('100%')
    .height('100%')
  }
}