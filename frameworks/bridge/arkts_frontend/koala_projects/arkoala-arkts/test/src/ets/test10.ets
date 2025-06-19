//import {AppStorageV2} from '@kit.ArkUI'
@Entry
@Component
struct EntryComponent10 {
  @State state : number = 2;
  build() {
    Column() {
      Button(`${this.state}`).onClick(()=>{
        this.state += 4;  // change state, will synchronize to its Child.
      })
      MyComponent10({link : this.state})
    }
  }
}

@Component
struct MyComponent10 {
  @State count: Resource = $r('sys.color.ohos_id_color_emphasize')
  @Link link : number;
  build() {
    Column() {
      Text(`Hello ${this.link}`)
        .fontColor(this.count)
      Button('change')
        .onClick(() => {
          this.link += 5 // change link, will sync back to its parent
        })
    }
  }
}
