// import { resourceManager } from '@kit.LocalizationKit';

@Entry
@Component
struct EntryComponent8 {
  build() {
    Column() {
      MyComponent8()
    }
  }
}

@Component
struct MyComponent8 {
  @State count: Resource = $r('sys.color.ohos_id_color_emphasize')

  build() {
    Column() {
      Text('Hello')
        .fontColor(this.count)
      Button('change')
        .onClick(() => {
          this.count = $r('sys.media.ohos_user_auth_icon_face');
        })
    }
  }
}
