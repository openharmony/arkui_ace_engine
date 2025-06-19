@Observed
class Task {
  isFinished: boolean = false;

  constructor(isFinished : boolean) {
    this.isFinished = isFinished;
  }
}

@Entry
@Component
struct ParentComponent {
  @State @Watch('onTaskAChanged') taskA: Task = new Task(false);
  @State @Watch('onTaskBChanged') taskB: Task = new Task(false);

  onTaskAChanged(changedPropertyName: string): void {
    console.log(`观测到父组件任务属性变化: ${changedPropertyName}`);
  }

  onTaskBChanged(changedPropertyName: string): void {
    console.log(`观测到父组件任务属性变化: ${changedPropertyName}`);
  }

  build() {
    Column() {
      Text(`父组件任务A状态: ${this.taskA.isFinished ? '已完成' : '未完成'}`)
      Text(`父组件任务B状态: ${this.taskB.isFinished ? '已完成' : '未完成'}`)
      ChildComponent({ taskA: this.taskA, taskB: this.taskB })
      Button('切换任务状态')
        .onClick(() => {
          this.taskB = new Task(!this.taskB.isFinished);
          this.taskA = new Task(!this.taskA.isFinished);
        })
    }
  }
}

@Component
struct ChildComponent {
  @ObjectLink @Watch('onObjectLinkTaskChanged') taskB: Task;
  @Link @Watch('onLinkTaskChanged') taskA: Task;

  onObjectLinkTaskChanged(changedPropertyName: string): void {
    console.log(`观测到子组件@ObjectLink关联的任务属性变化: ${changedPropertyName}`);
  }

  onLinkTaskChanged(changedPropertyName: string): void {
    console.log(`观测到子组件@Link关联的任务属性变化: ${changedPropertyName}`);
  }

  build() {
    Column() {
      Text(`子组件任务A状态: ${this.taskA.isFinished ? '已完成' : '未完成'}`)
      Text(`子组件任务B状态: ${this.taskB.isFinished ? '已完成' : '未完成'}`)
    }
  }
}
