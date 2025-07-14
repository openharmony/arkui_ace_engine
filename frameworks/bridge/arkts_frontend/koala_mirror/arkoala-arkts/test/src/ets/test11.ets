class Model11 {
  public value: string;
  constructor(value: string) {
    this.value = value;
  }
}

@Entry
@Component
struct EntryComponent11 {
  build() {
    Column() {
      // 此处指定的任何命名参数都将在初始渲染时
      // 覆盖本地定义的默认值
      MyComponent11({ count: 1, increaseBy: 2 })
      MyComponent11({ title: new Model11('Hello, World 2'), count: 7 })
    }
  }
}

@Component
struct MyComponent11 {

  @State title: Model11 = new Model11('local child value');
  @State count: number = 0;
  private increaseBy : number = 1;

  build() {
    Column() {
      Text(`count : ${this.count}  titleValue : ${this.title.value}`)
      Button() {
        Text(`Click to change title`).fontSize(10)
      }.onClick(() => {
        // @State变量的更新将触发上面的Text组件内容更新
        this.title.value = this.title.value == 'Hello Ace' ? 'Hello World' : 'Hello Ace';
      })

      Button() {
        Text(`Click to increase count=${this.count}`).fontSize(10)
      }.onClick(() => {
        // @State变量的更新将触发上面的Text组件内容更新
        this.count += this.increaseBy;
      })
    } // Column
  } // build
}
