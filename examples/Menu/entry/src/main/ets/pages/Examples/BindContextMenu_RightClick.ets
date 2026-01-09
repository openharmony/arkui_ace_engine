import { webview } from '@kit.ArkWeb';
import { pasteboard } from '@kit.BasicServicesKit';

const TAG = 'ContextMenu';

@Builder
export function BindContextMenuBuilder() {
  BindContextMenuTest()
}

@Entry
@Component
struct BindContextMenuTest {
  pageInfos: NavPathStack = new NavPathStack();
  controller: webview.WebviewController = new webview.WebviewController();
  private result: WebContextMenuResult | undefined = undefined;
  @State linkUrl: string = '';
  @State offsetX: number = 0;
  @State offsetY: number = 0;
  @State showMenu: boolean = false;
  uiContext: UIContext = this.getUIContext();

  @Builder
  // 构建自定义菜单及触发功能接口
  MenuBuilder() {
    // 以垂直列表形式显示的菜单。
    Menu() {
      // 展示菜单Menu中具体的item菜单项。
      MenuItem({content: '撤销',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.undo();
          this.showMenu = false;
        })
      MenuItem({content: '重做',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.redo();
          this.showMenu = false;
        })
      MenuItem({content: '粘贴为纯文本',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.pasteAndMatchStyle();
          this.showMenu = false;
        })
      MenuItem({content: '复制图片',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.copyImage();
          this.showMenu = false;
        })
      MenuItem({content: '剪切',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.cut();
          this.showMenu = false;
        })
      MenuItem({content: '复制',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.copy();
          this.showMenu = false;
        })
      MenuItem({content: '粘贴',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.paste();
          this.showMenu = false;
        })
      MenuItem({content: '复制链接',})
        .width(100)
        .height(50)
        .onClick(() => {
          let pasteData = pasteboard.createData('text/plain', this.linkUrl);
          pasteboard.getSystemPasteboard().setData(pasteData, (error) => {
            if (error) {
              return;
            }
          })
          this.showMenu = false;
        })
      MenuItem({content: '全选',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.selectAll();
          this.showMenu = false;
        })
    }
    .width(150)
    .height(450)
  }

  private iconStr: Resource = $r('app.media.app_icon')
  @State isShow: boolean = false
  @State isShow2: boolean = false

  private menuElementList: Array<MenuElement> = [
    { 
        value: '菜单一',
        icon: $r('app.media.app_icon'),
        action: () => {
            console.log('www data click on menu 1')
        }},
    { 
        value: '菜单二',
        icon: $r('app.media.app_icon'),
        action: () => {
            console.log('www data click on menu 2')
        }},
    { 
        value: '菜单三',
        icon: $r('app.media.app_icon'),
        action: () => {
            console.log('www data click on menu 3')
        }},
    { 
        value: '菜单四',
        icon: $r('app.media.app_icon'),
        action: () => {
            console.log('www data click on menu 4')
        }},
    { 
        value: '菜单五',
        icon: $r('app.media.app_icon'),
        action: () => {
            console.log('www data click on menu 5')
        }},
  ]

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({
        startIcon: this.iconStr,
        content: '菜单选项' 
      })
      MenuItem({
        startIcon: this.iconStr,
        content: '菜单选项'
      })
      MenuItem({
        startIcon: this.iconStr,
        content: '菜单选项'
      })
    }
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({space: 10}) {
          Web({ src: 'https://auth.huaweicloud.com/authui/login.html?locale=zh-cn&service=https%3A%2F%2Fwww.huaweicloud.com%2Fintl%2Fzh-cn%2F#/login'
            //$rawfile('index.html')
          , controller: this.controller })
          // 触发自定义弹窗
            .onContextMenuShow((event) => {
              if (event) {
                this.result = event.result
                console.info(TAG + 'x coord = ' + event.param.x());
                console.info(TAG + 'link url = ' + event.param.getLinkUrl());
                this.linkUrl = event.param.getLinkUrl();
              }
              console.info(TAG, `x: ${this.offsetX}, y: ${this.offsetY}`);
              this.offsetX = 0;
              this.offsetY = Math.max(this.uiContext!.px2vp(event?.param.y() ?? 0) - 0, 0);
              return true;
            })
            .bindContextMenu(this.MenuBuilder, ResponseType.RightClick, {
              enableArrow: false,
              placement: Placement.LeftTop,
              offset: {
                x: this.offsetX,
                y: this.offsetY
              },
              mask: false,
              aboutToAppear: () => {
                console.log('aboutToAppear----------')
              },

              onDisappear: () => {
                this.result!.closeContextMenu();
              },
            })
            .fileAccess(true)
            .javaScriptAccess(true)
            .domStorageAccess(true)
        }
        .width('100%')
        .height('100%')
      }
    }.title('BindContextMenu_RightClick')
    .onBackPressed(() => {
      // 弹出路由栈栈顶元素
      this.pageInfos.pop();
      return true;
    }).onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
    })
  }
}