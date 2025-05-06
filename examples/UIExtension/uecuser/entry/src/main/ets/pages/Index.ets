import { ComponentContent } from '@kit.ArkUI';
class Params {
}
@Builder
function loadingBuilder(params: Params) {
  Column() {
    LoadingProgress()
      .color(Color.Blue)
  }
}
@Builder
function areaChangePlaceHolderBuilder(params: Params) {
  Column() {
  }
  .width('100%')
  .height('100%')
  .backgroundColor(Color.Orange)
}
@Entry
@Component
struct Second {
  @State message1: string = 'Hello World 1'
  @State message2: string = 'Hello World 2'
  @State message3: string = 'Hello World 3'
  @State visible: Visibility = Visibility.Hidden
  @State wid: number = 300
  @State hei: number = 300
  private proxy: UIExtensionProxy | null = null;
  private initPlaceholder = new ComponentContent(this.getUIContext(), wrapBuilder(LoadingBuilder), new Params);
  private areaChangePlaceholder = new ComponentContent(this.getUIContext(),
    wrapBuilder(areaChangePlaceHolderBuilder), new Params);


  build() {
    Row() {
      Column() {
        Text(this.message1).fontSize(30)
        Text(this.message2).fontSize(30)
        Text(this.message3).fontSize(30)
        UIExtensionComponent({
          bundleName : 'com.example.newdemo',
          abilityName: 'UIExtensionProvider',
          parameters: {
            'ability.want.params.uiExtensionType': 'sys/commonUI'
          }},
          {
            placeholder: this.initPlaceholder,
            areaChangePlaceholder: {
              'FOLD_TO_EXPAND' : this.areaChangePlaceholder,
            }
          })
          .width(this.wid)
          .height(this.hei)
          .border({width: 5, color: Color.Blue})
          .onReceive((data) => {
            console.info('Lee onReceive, for test')
            this.message3 = JSON.stringify(data['data'])
          })
          .onTerminated((info) => {
            console.info('onTerminated: code =' + info.code + ', want = ' + JSON.stringify(info.want));
          })
          .onRemoteReady((proxy) => {
            console.info('onRemoteReady, for test')
            this.proxy = proxy

            this.proxy.on('syncReceiverRegister', syncRegisterCallback1);

            this.proxy.on('asyncReceiverRegister', (proxy1) => {
              console.info('on invoke for test, type is asyncReceiverRegister');
            });
          })

        Button('点击向UIExtensionAbility发送数据').onClick(() => {
          if (this.proxy != undefined) {
            this.proxy.send({data: '你好1'})

            try {
              let re = this.proxy.sendSync({data: '你好2'})
              console.info('for test, re=' + JSON.stringify(re));
            } catch (err) {
              console.error(`sendSync failed for test. errCode=${err.code}, msg=${err.message}`);
            }
          }
        })
      }
      .width('100%')
    }
    .height('100%')
  }
}

function syncRegisterCallback1(proxy: UIExtensionProxy) {
  console.info('on invoke for test, syncRegisterCallback1, type is syncReceiverRegister');
}

function syncRegisterCallback2(proxy: UIExtensionProxy) {
  console.info('on invoke for test, syncRegisterCallback2, type is syncReceiverRegister');
}