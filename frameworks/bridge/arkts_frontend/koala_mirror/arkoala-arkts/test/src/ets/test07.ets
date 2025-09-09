@Entry
@Component
struct EntryComponent7 {
  build() {
    Column() {
      MyComponent7()
    }
  }
}

@Component
struct MyComponent7 {
  @State count: number | undefined = 0;

  build() {
    Column() {
      Text(`count(${this.count})`)
      Button('change')
        .onClick(() => {
          this.count = undefined;  // UI will be triggered
        })
    }
  }
}
