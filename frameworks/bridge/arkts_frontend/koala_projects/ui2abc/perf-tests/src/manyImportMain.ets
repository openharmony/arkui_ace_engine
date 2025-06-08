
/**
 * 多级import manyImportMain.ets
 */

import { Component, Column } from "@ohos.arkui"
import { ManyImportComponent1 } from "./manyImportFiles/manyImportFile1"

@Component
struct ManyImportMain {
    build() {
        Column() {
            ManyImportComponent1()
        }
    }
}
