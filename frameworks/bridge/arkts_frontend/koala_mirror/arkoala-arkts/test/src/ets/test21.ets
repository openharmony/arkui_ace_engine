@Observed
class Source {
  public source: number;

  constructor(source: number) {
    this.source = source;
  }
}

@Observed
class Data {
  public data: number;

  constructor(data: number) {
    this.data = data;
  }
}

@Entry
@Component
struct Parent21 {
  @State count: Source | Data | undefined = new Source(10);

  build() {
    Column() {
      Child21({ count: this.count })

      Button('change count property')
        .margin(10)
        .onClick(() => {
          // 判断count的类型，做属性的更新
          if (this.count instanceof Source) {
            this.count.source += 1;
          } else if (this.count instanceof Data) {
            this.count.data += 1;
          } else {
            console.info('count is undefined, cannot change property');
          }
        })

      Button('change count to Source')
        .margin(10)
        .onClick(() => {
          // 赋值为Source的实例
          this.count = new Source(100);
        })

      Button('change count to Data')
        .margin(10)
        .onClick(() => {
          // 赋值为Data的实例
          this.count = new Data(100);
        })

      Button('change count to undefined')
        .margin(10)
        .onClick(() => {
          // 赋值为undefined
          this.count = undefined;
        })
    }.width('100%')
  }
}

@Component
struct Child21 {
  @ObjectLink count: Source | Data | undefined;

  build() {
    Column() {
      Text(`count is instanceof ${this.count instanceof Source ? 'Source' :
        this.count instanceof Data ? 'Data' : 'undefined'}`)
        .fontSize(30)
        .margin(10)

      Text(`count's property is  ${this.count instanceof Source ? this.count.source : this.count?.data}`).fontSize(15)

    }.width('100%')
  }
}
