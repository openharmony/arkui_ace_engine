import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo memo_variables() {
        @memo const f = (): number => {
            return 123
        }, g = (x: number): number => {
            return 123 + x
        }
   
        const h = @memo (): number => {
            return 1
        }
   
        f()
        g(1)
        h()
    }
}
