import { Assert as assert, suite, test } from "@koalaui/harness"
import * as fs from "fs"

function assertUnmemoizedEqualGolden(filename: string) {
    const unmemoized = fs.readFileSync(`./test/unmemoized/${filename}`, "utf8");
    const golden = fs.readFileSync(`./test/golden/${filename}`, "utf8");
    return assert.equal(golden, unmemoized)
}

suite("Memo stable", () => {
    test("Memo stable rewrites: this management",
        () => assertUnmemoizedEqualGolden("examples/memo_stable.ts")
    )
})

suite("Union memo types", () => {
    test("Union type parameters",
        () => assertUnmemoizedEqualGolden("examples/union_type_parameters.ts")
    )
})

suite("Local export as", () => {
    test("Local export as",
        () => assertUnmemoizedEqualGolden("examples/localexported.ts")
    )
})
