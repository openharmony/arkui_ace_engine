import { AnimateCallback, CustomTransition } from './CustomTransitionUtils'

// PageTwo
@Builder
export function PageTwoBuilder() {
  PageContainer({ title: "PageTwo" });
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
      (isPush: boolean, isExit: boolean) => {
        if (isPush) {
          if (isExit) {
            this.opacityValue = 1;
          } else {
            this.opacityValue = 0;
          }
        } else {
          if (isExit) {
            this.opacityValue = 1;
          } else {
            this.opacityValue = 1;
          }
        }
      },
      // 设置转场动画终点，根据不同的转场类型分别设置
      (isPush: boolean, isExit: boolean) => {
        if (isPush) {
          if (isExit) {
            this.opacityValue = 1;
          } else {
            this.opacityValue = 1;
          }
        } else {
          if (isExit) {
            this.opacityValue = 0;
          } else {
            this.opacityValue = 1;
          }
        }
      });
  }

  build() {
    NavDestination() {
      Column() {
        Button('点击跳转PageOne', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pop();
          })
        Text('\n')
        Button('点击跳转PageThree', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'PageThree' });
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
    .opacity( this.opacityValue)
  }
}