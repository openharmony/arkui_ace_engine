import { AnimateCallback, CustomTransition } from './CustomTransitionUtils'

// PageOne
@Builder
export function PageOneBuilder() {
  PageContainer({ title: "PageOne" });
}

@Component
export struct PageContainer {
  pageInfos: NavPathStack = new NavPathStack();
  @State opacityValue: number = 0;
  pageId: string = '';
  title: string = ''

  registerCallback() {
    CustomTransition.getInstance().registerNavParam(this.pageId,
      // 设置转场动画起点，根据不同的转场类型分别设置
      (isPush: boolean, isExit: boolean) => {},
      // 设置转场动画终点，根据不同的转场类型分别设置
      (isPush: boolean, isExit: boolean) => {}
    );
  }

  build() {
    NavDestination() {
      Column() {
        Button('点击跳转点击跳转PageTwo', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'PageTwo' });
          })
      }
      .size({ width: '100%', height: '100%' })
    }
    .title(this.title)
    .onDisAppear(() => {
      // 页面销毁时解注册自定义转场动画参数
      CustomTransition.getInstance().unRegisterNavParam(this.pageId);
    })
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
      if (context.navDestinationId) {
        this.pageId = context.navDestinationId;
        // 页面创建时注册自定义转场动画参数
        this.registerCallback();
      }
    })

  }
}