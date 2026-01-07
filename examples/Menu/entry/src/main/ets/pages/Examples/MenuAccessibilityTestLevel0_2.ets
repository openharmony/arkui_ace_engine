import {MyComponent} from "../../common/MyComponent"
import {MenuBuilder, MenuAttrOptions } from "../../customBuilder/MenuBuilder"

@Extend(Text) function  paramTextStyle() {
  .fontSize(9)
  .width("100%")
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width("100%")
  .backgroundColor(Color.Pink)
}

@Entry
@Component
struct MenuAccessibilityTestLevel0_2 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0,]
  @State menuShow: boolean = false

  //图文菜单的option
  @State menuOptions: MenuOptions = {
    showInSubWindow: false
  }

  //Menu的builder option
  @State menuAttrOption: MenuAttrOptions = {
    submenuMode: 0
  }

  @Builder
  MenuBuilder() {
    MenuBuilder({
        menuAttrOptions: {
            submenuMode: this.menuAttrOption.submenuMode
        }
    })
  }
  @Builder
  PreviewBuilder() {
    Image($r('app.media.app_icon'))
      .width(200)
      .height(120)
  }

  build() {
    Scroll(this.scroller){
      Column({ space: 5 }) {
        Text(`验证bindContextMenu菜单无障碍功能`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`设置菜单次级菜单类型: ${this.menuAttrOption.submenuMode}`)
            .paramTextStyle()
          Row({space: 3}){
            MyComponent({title: 'SIDE', func: () => {
              this.menuAttrOption.submenuMode = 0
            }})
            MyComponent({title: 'EMBEDDED', func: () => {
              this.menuAttrOption.submenuMode = 1
            }})
            MyComponent({title: 'STACK', func: () => {
              this.menuAttrOption.submenuMode = 2
            }})
          }

          Button('bindContextMenu: preview_none')
            .backgroundColor(Color.Orange)
            .borderRadius(0)
            .bindContextMenu(this.menuShow!!, this.MenuBuilder(), {
              preview: MenuPreviewMode.NONE
            })
            .onClick( () => {
              if (this.menuShow != true) {
                this.menuShow = true
              }
            })
          Button('bindContextMenu: preview_image')
            .backgroundColor(Color.Orange)
            .borderRadius(0)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: MenuPreviewMode.IMAGE
            })
          Button('bindContextMenu: preview_custom')
            .backgroundColor(Color.Orange)
            .borderRadius(0)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: this.PreviewBuilder()
            })
        }
        .columnStyle()

      }
      .width('100%')
    }
    .padding(12)
    .align(Alignment.TopStart)
    .width("100%").height("100%")
    .scrollBar(BarState.Off)
  }
}