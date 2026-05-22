import { common } from '@kit.AbilityKit';
import { Router, router, window } from '@kit.ArkUI';
import testNapi from 'libentry.so';

const DOMAIN = 0x0000;

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';
  @State timeString: string = '';
  @State immenabled: boolean = false;
  @State windowId: number = 0;
  @State TE_displayId: number = 0;
  @State TE_windowId: number = 0;
  @State displayX: number = 0;
  @State displayY: number = 0;
  @State actionTime: number = -1;
  @State fingerId_0: number = 0;
  @State fingerId_1: number = 0;
  @State action_1: number = 3;
  @State action_0: number = 1;
  @State windowX: number = 587;
  @State windowY: number = 285;

  context = this.getUIContext()?.getHostContext() as common.UIAbilityContext
  windowClass = this.context.windowStage.getMainWindowSync()
  sleep = (sleepMs: number) => new Promise<string>(resolve => setTimeout(resolve, sleepMs));

  build() {
    Column({space: 20}) {
      Column() {
        Button('点击获取时间判断页面可以响应：' + this.timeString)
          .onClick(()=>{
            this.timeString = new Date().toLocaleString();
            console.info(`time is ` + this.timeString)
          }).width('100%').type(ButtonType.Normal)
        Button().onClick(()=>{
            this.timeString = new Date().toLocaleString();
          }).width('100%').type(ButtonType.Normal)
      }
      Text('HelloWorld')
        .id('HelloWorld')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Button('测试InjectEvent').width('100%').onClick(() => {
        try {
          this.message = String(testNapi.injectEvent(this.windowId, this.TE_displayId, this.windowX, this.windowY, this.action_0, this.fingerId_0, this.displayX, this.displayY, this.actionTime, this.windowId));
          this.message = String(testNapi.injectEvent(this.windowId, this.TE_displayId, this.windowX, this.windowY, this.action_1, this.fingerId_0, this.displayX, this.displayY, this.actionTime, this.windowId));
        } catch (e) {
          console.error(`failed to TestInjectEvent. Cause code: ${e.code}, message: ${e.message}`);
          this.message = String(e.code);
        }
      })

    }
    .width('100%').height('100%')
  }

  aboutToAppear() {
    try {
      const properties = this.windowClass.getWindowProperties();
      this.windowId = properties?.id;
      AppStorage.setOrCreate('ability_window_Id', this.windowId);
    } catch (error) {
      hilog.error(DOMAIN, 'testTag', JSON.stringify(error))
    }
  }
}