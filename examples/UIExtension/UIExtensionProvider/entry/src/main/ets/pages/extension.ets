import { UIExtensionContentSession } from '@kit.AbilityKit';

let storage = LocalStorage.getShared()
AppStorage.setOrCreate('message', 'UIExtensionAbility')

@Entry(storage)
@Component
struct Extension {
  @StorageLink('message') storageLink: string = '';
  private session: UIExtensionContentSession | undefined = storage.get<UIExtensionContentSession>('session');
  pathStack: NavPathStack = new NavPathStack()

  @Builder
  PageMap(name: string) {
    if (name === 'hello') {
      pageOneTmp()
    }
  }

  onPageShow() {
    if (this.session != undefined) {
      this.session.setReceiveDataCallback((data)=> {
        this.storageLink = JSON.stringify(data)
        console.info('invoke for test, handle callback set by setReceiveDataCallback successfully');
      })

      this.session.setReceiveDataForResultCallback(func1)
    }
  }

  build() {
    Navigation(this.pathStack) {
      Row() {
        Column() {
          Text(this.storageLink)
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
          Button('点击向Component发送数据').onClick(()=>{
            if (this.session != undefined) {
              this.session.sendData({'data': 543321})
              console.info('send 543321, for test')
            }
          })
          Button('terminate').onClick(()=> {
            if (this.session != undefined) {
              this.session.terminateSelf();
            }
            storage.clear()
          })
          Button('terminate with result').onClick(()=>{
            if (this.session != undefined) {
              this.session.terminateSelfWithResult({
                resultCode: 0,
                want: {
                  bundleName: 'myBundleName',
                  parameters: { 'result': 123456 }
                }
              })
            }
            storage.clear()
          })

          Button('点击跳转').onClick(()=> {
            this.pathStack.pushPath({ name: 'hello'})
          })
        }
      }
      .height('100%')
    }.navDestination(this.PageMap)
    .mode(NavigationMode.Stack)
  }
}

// pageOne
@Component
export struct pageOneTmp {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column() {
        Text('Hello World')
      }.width('100%').height('100%')
    }.title('pageOne')
    .onBackPressed(() => {
      const popDestinationInfo = this.pathStack.pop() // 弹出路由栈栈顶元素
      console.log('pop' + '返回值' + JSON.stringify(popDestinationInfo))
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}

function func1(data: Record<string, Object>): Record<string, Object> {
  let linkToMsg: SubscribedAbstractProperty<string> = AppStorage.link('message');
  linkToMsg.set(JSON.stringify(data))
  console.info('invoke for test, handle callback set by setReceiveDataForResultCallback successfully');
  return data;
}