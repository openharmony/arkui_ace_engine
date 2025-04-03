@Component
struct EntryComponent1 {
  @Prop prop : number = 2;
  build() {
    Column() {
      Button(`${this.prop}`).onClick(()=>{
        this.prop += 4;  // only received once, change prop,  will not synchronized to its Child.
      })
      MyComponent1({state : this.prop})
    }
  }
}

@Component
struct MyComponent1 {
  @State count: Resource = $r('sys.color.ohos_id_color_emphasize')
  @State state : number = 1;
  build() {
    Column() {
      Text(`Hello ${this.state}`)
        .fontColor(this.count)
      Button('change')
        .onClick(() => {
          this.count = $r('sys.media.ohos_user_auth_icon_face');
        })
    }
  }
}


