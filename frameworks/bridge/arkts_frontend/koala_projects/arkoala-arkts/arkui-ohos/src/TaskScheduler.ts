
const MAX_THREAD_COUNT: Int = 3;
type Task = () => void

export class TaskScheduler {
    private static current: TaskScheduler | undefined = undefined

    private static maxThreadCount: Int = MAX_THREAD_COUNT
    private managerWorker: EAWorker
    private workers: EAWorker[] = []
    private idleWorkers: EAWorker[] = []
    private tasks: Task[] = []

    static get instance(): TaskScheduler {
        let current = TaskScheduler.current
        if (current === undefined) {
            current = new TaskScheduler()
            TaskScheduler.current = current
        }
        return current
    }

    constructor(count?: Int) {
        this.managerWorker = new EAWorker();
        this.managerWorker.start()
        this.addWorker();
    }

    addWorker() {
        if (this.workers.length == TaskScheduler.maxThreadCount) {
            return
        }
        let worker = new EAWorker();
        worker.start()
        this.workers.push(worker)
        this.addIdleWorker(worker)

    }

    addIdleWorker(worker: EAWorker) {
        if (this.tasks.length > 0) {
            let task = this.tasks.shift()
            this.runTask(this.managerWorker, worker, task!)
            return;
        }
        this.idleWorkers.push(worker)
    }

    submit(task: () => void) {
        let managerWorker = this.managerWorker
        managerWorker.run<void>(() => {
            if (this.idleWorkers.length == 0) {
                this.addWorker()
            }
            if (this.idleWorkers.length > 0) {
                let worker = this.idleWorkers.shift()
                this.runTask(managerWorker, worker!, task)
                return
            }
            this.tasks.push(task)
        })
    }

    runTask(managerWorker: EAWorker, worker: EAWorker, task: () => void) {
        worker!.run<void>(() => {
            task()
            managerWorker.run<void>(() => {
                this.addIdleWorker(worker!)
            })
        })
    }

    static postToMain(task: () => void) {
        EAWorker.postToMain<void>(task)
    }

}