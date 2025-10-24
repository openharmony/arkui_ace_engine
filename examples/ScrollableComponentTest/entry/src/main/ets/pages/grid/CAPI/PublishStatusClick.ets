import { BusinessError,commonEventManager } from '@kit.BasicServicesKit';

@Component
export struct StatusClickComponent {
  build() {
    Button('publicClick').onClick(() => {
      // 发布公共事件
      try {
        commonEventManager.publish("usual.event.STATUSBAR_CLICKED", (err: BusinessError)=>{
          if (err) {
            console.error(`wangyu publish failed, code is ${err.code}, message is ${err.message}`);
          } else {
            console.info("wangyu publish success");
          }
        });
      } catch (error) {
        let err: BusinessError = error as BusinessError;
        console.error(`publish failed, code is ${err.code}, message is ${err.message}`);
      }
    }).width(100).height(50).margin(10)
  }
}