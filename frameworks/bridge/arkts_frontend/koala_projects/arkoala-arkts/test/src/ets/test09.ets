@Entry
@Component
struct EntryComponent {
  @State state : number = 2;
  build() {
    Column() {
      Button(`${this.state}`).onClick(()=>{
        this.state += 4;  // change state, will synchronize to its Child.
      })
      MyComponent({prop : this.state})
    }
  }
}

@Component
struct MyComponent {
  @State count: Resource = $r('sys.color.ohos_id_color_emphasize')
  @Prop prop : number = 1;
  build() {
    Column() {
      Text(`Hello ${this.prop}`)
        .fontColor(this.count)
      Button('change')
        .onClick(() => {
          this.prop += 5 // change prop, will not sync back to its parent
        })
    }
  }
}
