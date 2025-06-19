import { Assert } from "@koalaui/harness"
import { AppControl, TaskType } from "./loader"

export function entry(control: AppControl) {
    suite("Case1", () => {
        test("StateChange:Increment", () => {
            const expected = "Case1 - value:1\nCase1 - value:2\nCase1 - value:3\n"
            const componentId = 42 // id from Case1.TestComponent
            // onChange
            const actual = control
                .loadPage("Case1")
                .start()
                .emitTask(TaskType.OnChange, componentId).nextFrame()
                .emitTask(TaskType.OnChange, componentId).nextFrame()
                .emitTask(TaskType.OnChange, componentId).nextFrame()
                .stop()
                .getLog()
            Assert.equal(expected, actual, "StateChange: Case1 test is failed!")
        })
    })
    suite("Case2", () => {
        test("StateChange:Decrement", () => {
            const expected = "Case2 - value:-1\nCase2 - value:-2\nCase2 - value:-3\n"
            const componentId = 42 // id from Case2.TestComponent
            // onChange
            const actual = control
                .loadPage("Case2")
                .start()
                .emitTask(TaskType.OnChange, componentId).nextFrame()
                .emitTask(TaskType.OnChange, componentId).nextFrame()
                .emitTask(TaskType.OnChange, componentId).nextFrame()
                .stop()
                .getLog()
            Assert.equal(expected, actual, "StateChange: Case2 test is failed!")
        })
    })
}
